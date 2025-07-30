# Magnoquill

Recently, I came across this <a href="http://tiny.cc/qpcq001" target="_blank" rel="noopener noreferrer">post</a> on LinkedIn. It refers to a Wolfram Community post that explains where the name "<a href="https://community.wolfram.com/groups/-/m/t/3516580" target="_blank" rel="noopener noreferrer">Magnoquill Driftflare Quiverbloom</a>" came from. That post presents a Mathematica translation of an animation originally created in <a href="https://p5js.org/" target="_blank" rel="noopener noreferrer">p5.js</a> -- is a useful tool for learning to code and make art (I had never heard of it before, sorry!) by <i>yuruyurau</i>.

Specifically, it uses these formulas $$\sin(x), \cos(x), \sqrt{x} \text{ and } x^2$$ combined in a way that they gradually generate points during calculation.

```javascript
a=(x,y,d=mag(k=(4+sin(x/11+t*8))*cos(x/14),e=y/8-19)+sin(y/9+t*2))=>
  point((q=2*sin(k*2)+sin(y/17)*k*(9+2*sin(y-d*3)))+50*cos(c=d*d/49-t)+200,
        q*sin(c)+d*39-440)

t=0,draw=$=>{
  t||createCanvas(w=400,w);
  background(9).stroke(w,96);
  for(t+=PI/240,i=1e4;i--;)a(i,i/235)
}
```

When these points are calculated and drawn one after another, they create shapes that move and look interesting.
The cool thing is that simple math formulas can make these rich and surprising pictures.

That's my attempt to reproduce it in C.

We chose the PPM format (Portable Pixel Map) because it is simple. 
In a nutshell, this format stores color images by saving the RGB values for each pixel. 
The file starts:
    - with a header that specifies the format (in our case, P6, which is binary and faster to read), 
    - the image size, and 
    - the type. 

After the header, the pixel data is stored from left to right and top to bottom, with the origin (0,0) at the top-left corner.


To speed up the process, I used <a href="https://ffmpeg.org/" target="_blank" rel="noopener noreferrer">ffmpeg</a> because I’m not yet ready to write all the code needed to create MP4 files from scratch.

![Animation preview](https://raw.githubusercontent.com/FrancescoPaoloL/Magnoquill/main/images/output.gif)



## Development Environment

- **OS:** Linux 6.1.0-37-amd64 Debian 6.1.140-1 (2025-05-22) x86_64 GNU/Linux  
- **Compiler:** gcc 12.2.0 (Debian 12.2.0-14+deb12u1)  
- **FFmpeg:** 5.1.6-0+deb12u1

## Build

Run:

```
make
```

## Run

```
 ./bin/magnoquill
```

