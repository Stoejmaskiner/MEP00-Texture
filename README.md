# MEP00 - Texture

> **Disclaimer:** this is an abandoned older prototype of the plugin, it was re-written from scratch [here](https://github.com/Stoejmaskiner/mep00-texture)

***product type:** [Meta Effect Plugin (MEP)]()*

***category:** creative effect, sound design*

Texture is a plugin that adds white noise correlated with the input signal. Give it a tonal sound and it will make it a noisy sound.

It has two modes: simple and gritty. Simple mode simply ring modulates white noise to the input and sums it, while gritty mode half-wave rectifies the white noise and squares it to make it more akin dense dust noise; then the dust noise is ring modulated with the rectified version of the input and summed together.

Optionally, the noise can be shaped with gentle 6dB low cut and high cut filters before summing with the input.

**Block diagram of simple mode**

```mermaid
flowchart LR
in[/input/]
white[/white noise/]
mul((X))
in --> mul
white --> mul --> gain
add((+))
in --> add
gain --> add
out[/output/]
add --> out

```

**Block diagram of gritty mode**

```mermaid
flowchart LR
in[/input/]
out[/output/]
white[/white noise/]
rect_h[half wave rectify]
pow[x^2]
rect_f[full wave rectify]
add((+))
mul((X))
in --> rect_f --> mul
in --> add
white --> rect_h --> pow --> mul --> gain --> add --> out
```

## Shared Processors Used

Texture is a meta-plugin, so it is developed for the purpose of testing code that will be used in larger projects in the future. This "shared code" is encapsulated into objects called "processors", these processors are used across multiple Støjmaskiner products. While other products are closed source, all meta-plugins are open source as well as the shared code library they help develop.

The processors used are the following:

- [RingModNoise]()
- [RingModDust]()
