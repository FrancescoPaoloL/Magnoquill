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
To make the process faster, I used  <a href="https://ffmpeg.org/" target="_blank" rel="noopener noreferrer">ffmpeg</a>, a powerful tool for handling video and audio. I chose this because I don’t think I’m ready to write all the code needed to create MP4 files on my own yet

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

