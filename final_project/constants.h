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

//AImode
#define WANDER 0
#define TRACE 1

//wander mode
#define WALLL 0
#define WALLR 1
#define PLATFORMLB 2
#define PLATFORMRB 3

struct startP {
	int x, y;
};