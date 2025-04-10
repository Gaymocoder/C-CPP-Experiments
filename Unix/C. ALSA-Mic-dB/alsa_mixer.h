#ifndef __ALSA_REQUESTS_H__
#define __ALSA_REQUESTS_H__

#include <alsa/asoundlib.h>

int init_sound_device_mixer(snd_mixer_t** mixer_handle_ptr, const char* device_name);
void close_sound_device_mixer(snd_mixer_t* mixer_handle_ptr, const char* device_name); 

int get_percent_selem_playback_volume(snd_mixer_elem_t* selem);
int get_percent_selem_capture_volume(snd_mixer_elem_t* selem);
int get_sound_device_name(int device_index, char** name);

int print_sound_devices();
int print_sound_mixers();
void print_mixer_selems(snd_mixer_t* mixer_handle);
void print_mixer_selem_info(snd_mixer_elem_t* selem);

#endif
