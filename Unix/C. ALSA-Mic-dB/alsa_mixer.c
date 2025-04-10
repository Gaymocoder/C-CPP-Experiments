#include "alsa_mixer.h"

#include <stdio.h>
#include <stdlib.h>

int init_sound_device_mixer(snd_mixer_t** mixer_handle_ptr, const char* device_name)
{
    if (snd_mixer_open(mixer_handle_ptr, 0))
    {
        fprintf(stderr, "Failed to open sound mixer\n");
        return 1;
    }
    
    // fprintf(stderr, "Sound mixer opened (%p)\n", handle);
    if (snd_mixer_attach(*mixer_handle_ptr, device_name))
    {
        fprintf(stderr, "Failed to attach sound device to the mixer: \"%s\"\n", device_name);
        return 1;
    }
    // fprintf(stderr, "Sound device to the mixer attached (%p): \"%s\"\n", handle, sound_device_name);
    
    if (snd_mixer_selem_register(*mixer_handle_ptr, NULL, NULL))
    {
        fprintf(stderr, "Failed to register mixer simple element class\n");
        return 2;
    }
    // fprintf(stderr, "Mixer simple element class registered (%p)\n", handle);
    
    if (snd_mixer_load(*mixer_handle_ptr))
    {
        fprintf(stderr, "Failed to load \"%s\"-mixer\n", device_name);
        return 3;
    }
    // fprintf(stderr, "\"%s\"-mixer loaded (%p)\n", sound_device_name, handle);
    
    return 0;
}

void close_sound_device_mixer(snd_mixer_t* mixer_handle_ptr, const char* device_name)
{
    snd_mixer_free(mixer_handle_ptr);
    snd_mixer_detach(mixer_handle_ptr, device_name);
    snd_mixer_close(mixer_handle_ptr);
}

int get_sound_device_name(int device_index, char** name)
{
    void** hints;
    if (snd_device_name_hint(device_index, "ctl", &hints))
    {
        fprintf(stderr, "Failed to get sound devices name hint\n");
        return 1;
    }
    
    *name = snd_device_name_get_hint(*hints, "NAME");
    if (!*name)
    {
        fprintf(stderr, "Failed to get name of the device from the hint\n");
        snd_device_name_free_hint(hints);
        return 2;
    }
    
    snd_device_name_free_hint(hints);
    return 0;
}

int get_percent_selem_playback_volume(snd_mixer_elem_t* selem)
{
    long min_volume, max_volume, curr_volume;
    snd_mixer_selem_get_playback_volume_range(selem, &min_volume, &max_volume);
    snd_mixer_selem_get_playback_volume(selem, 0, &curr_volume);
    
    return (int) ((curr_volume - min_volume) * 100 / (max_volume - min_volume));
}
    
int get_percent_selem_capture_volume(snd_mixer_elem_t* selem)
{
    long min_volume, max_volume, curr_volume;
    snd_mixer_selem_get_capture_volume_range(selem, &min_volume, &max_volume);
    snd_mixer_selem_get_capture_volume(selem, 0, &curr_volume);
    
    return (int) ((curr_volume - min_volume) * 100 / (max_volume - min_volume));
}

int print_sound_devices()
{
    void** hints;
    if (snd_device_name_hint(-1, "ctl", &hints))
    {
        fprintf(stderr, "Failed to get sound devices name hint\n");
        return 1;
    }
    
    for(int i = 0; hints[i]; ++i)
    {
        char* name = snd_device_name_get_hint(hints[i], "NAME");
        if (!name)
        {
            fprintf(stderr, "Failed to get name of the device from the hint\n");
            snd_device_name_free_hint(hints);
            return 2;
        }
        
        char* description = snd_device_name_get_hint(hints[i], "DESC");
        if (!description)
        {
            fprintf(stderr, "Failed to get description of the device from the hint\n");
            snd_device_name_free_hint(hints);
            free(name);
            return 3;
        }
        
        printf("Sound device %i — \"%s\"\n%s\n\n", i, name, description);
        
        free(description);
        free(name);
    }
    
    snd_device_name_free_hint(hints);
    return 0;
}

int print_sound_mixers()
{
    int error_code = 0;
    snd_mixer_t* handle;
    
    int card_index = -1;
    if (snd_card_next(&card_index))
    {
        fprintf(stderr, "Failed to get sound card index\n");
        return 1;
    }
    
    while (card_index != -1)
    {
        char* card_name;
        if (snd_card_get_name(card_index, &card_name))
        {
            fprintf(stderr, "Failed to get sound card's name\n");
            return 2;
        }
        
        char* card_system_name;
        if (get_sound_device_name(card_index, &card_system_name))
        {
            fprintf(stderr, "Failed to get sound card's system name\n");
            free(card_name);
            return 3;
        }
        
        printf("Card %i — \"%s\" (system name: \"%s\")\n", card_index, card_name, card_system_name);
        
        
        if (init_sound_device_mixer(&handle, card_system_name))
        {
            fprintf(stderr, "Failed to init sound device mixer (card_system_name = \"%s\")\n", card_system_name);
            free(card_system_name);
            free(card_name);
            return 4;
        }
        
        print_mixer_selems(handle);
        
        close_sound_device_mixer(handle, card_system_name);
        free(card_system_name);
        free(card_name);
        
        if (snd_card_next(&card_index))
        {
            fprintf(stderr, "Failed to get sound card index\n");
            return 1;
        }
    }
    
    return 0;
}

void print_mixer_selems(snd_mixer_t* mixer_handle)
{
    for(snd_mixer_elem_t* selem = snd_mixer_first_elem(mixer_handle); selem; selem = snd_mixer_elem_next(selem))
        print_mixer_selem_info(selem);
}

void print_mixer_selem_info(snd_mixer_elem_t* selem)
{
    long capture_dB_x100 = 0, playback_dB_x100 = 0;
    int capture_volume = 0, playback_volume = 0;
    
    unsigned int index = snd_mixer_selem_get_index(selem);
    const char* name = snd_mixer_selem_get_name(selem);
    
    int active = snd_mixer_selem_is_active(selem);
    int capture = snd_mixer_selem_has_capture_volume(selem);
    int playback = snd_mixer_selem_has_playback_volume(selem);
    
    char description[100] = "";
    strncat(description, active  ? "Active " : "Non-active ", 11);
    strncat(description, capture ? "capture " : "", 8);
    strncat(description, (playback && capture)  ? "and playback " : "", 13);
    strncat(description, (!capture && playback) ? "playback " : "", 9);
    printf("Simple Mixer %u: %s\n%sdevice\n", index, name, description);
    
    if (capture)
    {
        snd_mixer_selem_get_capture_dB(selem, 0, &capture_dB_x100);
        capture_volume = get_percent_selem_capture_volume(selem);
        printf("Capture volume: %i%% (%.2f dB)\n", capture_volume, ((double) capture_dB_x100) / 100);
    }
    
    if (playback)
    {
        snd_mixer_selem_get_playback_dB(selem, 0, &playback_dB_x100);
        playback_volume = get_percent_selem_playback_volume(selem);
        printf("Playback volume: %i%% (%.2f dB)\n", playback_volume, ((double) playback_dB_x100) / 100);
    }
    
    printf("\n");
}
