#pragma once
#define WIDTH 3840
#define HEIGHT 2560
#define ALLREGION -1
#define WINDOWW 960
#define WINDOWH 640
#define CAMERAW   WINDOWW
#define CAMERAH   WINDOWH
#define VELOCITY 4
#define SHRINK 1
#define MAPTILEX 120
#define MAPTILEY 80
#define NO_TRANSPARENT_BG {0, 0, 0, 0}
#define MAXHP 8
#define SOLID 100
#define SHADED 101
#define BLENDED 102

//AImode
#define WANDER 0
#define TRACE 1

//wander mode
#define WALLL 0
#define WALLR 1
#define PLATFORMLB 2
#define PLATFORMRB 3

//for music
#define MUSIC 10
#define EFFECT 11
#define FOREVER -1
#define ONE 0
#define ALLCHANNEL -1

struct startP {
	int x, y;
};
