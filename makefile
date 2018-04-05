CXX = $(CROSS_COMPILE)g++
##compiler for c++

SAMPLE1_APP = ./bin/Oilpaintingeffect
SAMPLE2_APP = ./bin/filmeffect
SAMPLE3_APP = ./bin/denoising
SAMPLE4_APP = ./bin/colordithering
SAMPLE5_APP = ./bin/graydithering
SAMPLE6_APP = ./bin/errdiffusion
SAMPLE7_APP = ./bin/stitching
SAMPLE8_APP = ./bin/puzzle
SAMPLE9_APP = ./bin/sobel
SAMPLE10_APP = ./bin/geometric
SAMPLE11_APP = ./bin/texture


##applications

##CFLAGS= -g -DPRINT_OUTPUT	
##for debugging

COMMON_OBJS= Operations.o \
			  iostring.o \
			 
##for common user made header files

SAMPLE1_OBJS = Oil_Painting_Effect.o
SAMPLE2_OBJS = Film_Effect.o
SAMPLE3_OBJS = Denoising.o
SAMPLE4_OBJS = Color_Dithering.o
SAMPLE5_OBJS = Gray_Dithering.o
SAMPLE6_OBJS = Error_Diffusion.o
SAMPLE7_OBJS = Panoramic_stitching.o
SAMPLE8_OBJS = Puzzle.o
SAMPLE9_OBJS = sobel.o
SAMPLE10_OBJS = Square_to_circle.o
SAMPLE11_OBJS = Texture_Classification.o

##for output files


LIB= 
##for external header files downloaded from the internet eg

LDFLAGS= -lm
##loader files :for header files like math.h (for -lm)

vpath %.cpp ./src
##path for  the source files

all: ${SAMPLE1_APP} ${SAMPLE2_APP} ${SAMPLE3_APP} ${SAMPLE4_APP} ${SAMPLE5_APP} ${SAMPLE6_APP} ${SAMPLE7_APP} ${SAMPLE8_APP} ${SAMPLE9_APP} ${SAMPLE10_APP} ${SAMPLE11_APP} ${SAMPLE12_APP} ${SAMPLE13_APP} ${SAMPLE14_APP} ${SAMPLE15_APP} ${SAMPLE16_APP}
##to run all the files keep adding all the file things

oil_painting:	 ${SAMPLE1_APP}
film:   ${SAMPLE2_APP}
denoising:   ${SAMPLE3_APP}
color_dithering:    ${SAMPLE4_APP} 
gray_dithering: ${SAMPLE5_APP} 
error_diffusion:	 ${SAMPLE6_APP} 
Panoramic_stitching: ${SAMPLE7_APP}
puzzle: ${SAMPLE8_APP}
sobel: ${SAMPLE79_APP}
square_to_circle: ${SAMPLE10_APP}
texture: ${SAMPLE711_APP}


## $@ for the lhs in green. goes to the source path

##this is where the make file starts

.cpp.o:
	${CXX} ${CFLAGS} ${INCLUDE} -c $< ${LIB} ${LDFLAGS} -o $@

${SAMPLE1_APP}: ${COMMON_OBJS} ${SAMPLE1_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE1_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE2_APP}: ${COMMON_OBJS} ${SAMPLE2_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE2_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE3_APP}: ${COMMON_OBJS} ${SAMPLE3_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE3_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE4_APP}: ${COMMON_OBJS} ${SAMPLE4_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE4_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE5_APP}: ${COMMON_OBJS} ${SAMPLE5_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE5_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE6_APP}: ${COMMON_OBJS} ${SAMPLE6_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE6_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE7_APP}: ${COMMON_OBJS} ${SAMPLE7_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE6_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE8_APP}: ${COMMON_OBJS} ${SAMPLE8_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE6_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE9_APP}: ${COMMON_OBJS} ${SAMPLE9_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE6_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE10_APP}: ${COMMON_OBJS} ${SAMPLE10_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE6_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}

${SAMPLE11_APP}: ${COMMON_OBJS} ${SAMPLE11_OBJS}
	${CXX} ${COMMON_OBJS} ${SAMPLE6_OBJS} ${CFLAGS} ${INCLUDE} -o $@ ${LIB} ${LDFLAGS}


clean:
	rm -rf *.o
	rm -rf ./bin/*





