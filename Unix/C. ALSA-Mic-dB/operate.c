#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include "alsa_mixer.h"

int main(int argc, char** argv)
{
    if (argc < 6 || (argc == 2 && strcmp(argv[1], "--help")))
    {
        fprintf(stderr, "Usage: ./<exe_name> <system_device_name> <simple_mixer_id> <simple_mixer_name> <capture/playback> <dB_x100>\n");
        return 1;
    }
    
    snd_mixer_t* handle;
    if (init_sound_device_mixer(&handle, argv[1]))
    {
        fprintf(stderr, "Failed to find initialize sound device mixer\n");
        return 2;
    }
    
    snd_mixer_selem_id_t* sid;
    if (snd_mixer_selem_id_malloc(&sid))
    {
        fprintf(stderr, "Failed to allocate snd_mixer_selem_id_t* object\n");
        return 3;
    }
    
    errno = 0;
    unsigned long index = strtoul(argv[2], NULL, 10);
    if (errno || index > UINT_MAX)
    {
        fprintf(stderr, "Failed to get simple mixer handle: wrong index\n");
        return 4;
    }
    
    long dB_x100 = 0, old_dB_x100 = 0;
    snd_mixer_elem_t* elem;
    snd_mixer_selem_id_set_index(sid, (unsigned int) index);
    snd_mixer_selem_id_set_name(sid, argv[3]);
    elem = snd_mixer_find_selem(handle, sid);
    if (!elem)
    {
        fprintf(stderr, "Failed to find simple mixer in \"%s\"-mixer\n", argv[1]);
        return 5;
    }
    
    if (!strcmp(argv[4], "capture"))
    {
        if (!snd_mixer_selem_has_capture_volume(elem))
        {
            fprintf(stderr, "Failed to set the volume: specified device doesn't have capture volume\n");
            return 6;
        }
        
        long min_dB_x100 = 0, max_dB_x100 = 0;
        if (snd_mixer_selem_get_capture_dB_range(elem, &min_dB_x100, &max_dB_x100))
        {
            fprintf(stderr, "Failed to get capture volume ranges\n");
            return 8;
        }
        
        errno = 0;
        dB_x100 = strtol(argv[5], NULL, 10);
        if (errno != 0 || dB_x100 < min_dB_x100 || dB_x100 > max_dB_x100)
        {
            fprintf(stderr, "Failed to set capture volume: out of dB_x100 range (should be integer value from %li to %li)\n", min_dB_x100, max_dB_x100);
            return 9;
        }
        
        if (snd_mixer_selem_get_capture_dB(elem, 0, &old_dB_x100))
        {
            fprintf(stderr, "Failed to get current capture volume\n");
            return 10;
        }
        
        if (snd_mixer_selem_set_capture_dB(elem, 0, dB_x100, 0))
        {
            fprintf(stderr, "Failed to set capture dB\n");
            return 11;
        }
    }
    else if (!strcmp(argv[4], "playback"))
    {
        if (!snd_mixer_selem_has_playback_volume(elem))
        {
            fprintf(stderr, "Failed to set the volume: specified device doesn't have playback volume\n");
            return 6;
        }
        
        long min_dB_x100 = 0, max_dB_x100 = 0;
        if (snd_mixer_selem_get_playback_dB_range(elem, &min_dB_x100, &max_dB_x100))
        {
            fprintf(stderr, "Failed to get playback volume ranges\n");
            return 8;
        }
        
        errno = 0;
        dB_x100 = strtol(argv[5], NULL, 10);
        if (errno != 0 || dB_x100 < min_dB_x100 || dB_x100 > max_dB_x100)
        {
            fprintf(stderr, "Failed to set playback volume: out of dB_x100 range (should be integer value from %li to %li)\n", min_dB_x100, max_dB_x100);
            return 9;
        }
        
        if (snd_mixer_selem_get_playback_dB(elem, 0, &old_dB_x100))
        {
            fprintf(stderr, "Failed to get current playback volume\n");
            return 10;
        }
        
        if (snd_mixer_selem_set_playback_dB(elem, 0, dB_x100, 0))
        {
            fprintf(stderr, "Failed to set playback dB\n");
            return 11;
        }
    }
    
    printf("Successfully changed the volume of \"%s\"-mixer (\"%s\"-selem) from %.2fdB to %.2fdB\n", argv[1], argv[3], (double) old_dB_x100 / 100.0, (double) dB_x100 / 100.0);
    
    return 0;
}
