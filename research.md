Alsa tutorials:
https://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m.html

https://soundprogramming.net/programming/alsa-tutorial-1-initialization/

Guitar effects:
https://github.com/Quinny/GuitarEffects/blob/master/README.md

https://daisy.audio/

https://github.com/thestk/rtaudio

json parsing
https://codezup.com/how-to-work-with-json-data-in-cpp-a-practical-guide/


commands for alsa sound loopback

Nice — you want a *virtual* ALSA device that you can play audio *to* (so other programs think they’re outputting) and record *from* (so other programs can capture what was played). The usual, simplest approach is to use ALSA's loopback kernel module (`snd-aloop`). Below I give a complete, ready-to-run recipe: load the loopback, optional nice `~/.asoundrc` aliases, quick shell commands using `aplay`/`arecord`/`ffmpeg`, and minimal C examples (capture & playback) that use the loopback device directly.

---

# 1) Load the loopback module

Run as root (or use `sudo`):

```bash
# load the module now
sudo modprobe snd-aloop

# optionally ensure it loads on boot (Debian/Ubuntu example)
echo "snd-aloop" | sudo tee /etc/modules-load.d/snd-aloop.conf
```

After loading, ALSA exposes a "Loopback" card. On many systems it becomes `hw:Loopback` or `hw:1` depending on existing cards. You can inspect with:

```bash
aplay -l
arecord -l
```

You should see something like `card X: Loopback [Loopback], device 0: Loopback PCM...` with at least two subdevices:

* playback subdevice(s) on card's `pcm0p` (playback side),
* capture subdevice(s) on `pcm1c` (capture side).

Typical mapping when using `hw:Loopback`:

* Playback to `hw:Loopback,0,0` — writes to the loopback playback subdevice
* Capture from `hw:Loopback,1,0` — reads from the loopback capture subdevice

(If your `aplay -l` shows different indices, substitute them.)

---

# 2) Minimal `~/.asoundrc` (optional) — create nice names

Put this in `~/.asoundrc` so you can refer to `pcm.loopout` and `pcm.loopin`:

```text
pcm.loopout {
    type hw
    card Loopback
    device 0     # playback device (subdevice 0)
}

pcm.loopin {
    type hw
    card Loopback
    device 1     # capture device (subdevice 0 on the capture side)
}

ctl.loopback {
    type hw
    card Loopback
}
```

Now you can `-D loopout` and `-D loopin` in arecord/aplay and libraries that understand ALSA device names.

---

# 3) Quick manual test with `aplay` / `arecord` / `ffmpeg`

### Play a WAV (send audio into the virtual recorder)

```bash
# play a wav into the loopback playback subdevice
aplay -D hw:Loopback,0,0 song.wav
# or using the alias
aplay -D loopout song.wav
```

### Record whatever is being played (capture from the other end)

Start recording in another terminal *before* or while you play:

```bash
arecord -D hw:Loopback,1,0 -f cd recorded.wav
# or using alias
arecord -D loopin -f cd recorded.wav
```
