# daBomb Asset build system
#
# John Adams
# jna@retina.net
# 4/2019 (originally from our Ides of DEF CON badge)
#
# Master SD CARD makefile
#
# This Makefile will build the tools and media that will be placed on
# the microSD cards.
#
# ImageMagick, and FFMPeg are required to convert images.
# the Makefile in the $(TOOLS_DIR)/ subdir will build our required tools
#
# Videos will not be built by this script. We will only copy .vid
# files to the sdcard from the video/ subdir.
#

# The tools dir contains our conversion tools and scripts
TOOLS_DIR = ../tools

# where we will stage our build before sdcard copy
STAGING_DIR = build

# The name of the sdcard to copy to (OSX only)
VOLNAME= /Volumes/DA_BOMB

.PHONY: tools_dep dirs

all: dirs tools_dep images video sounds photos sdcard

tools_dep:
	$(MAKE) -C $(TOOLS_DIR)

# These rules will build the standard images only if the source images
# have changed.

rgb/doom/%.rgb : jpg/doom/%.jpg
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh $<
	mv $(subst .jpg,.rgb,$<) $(@)

rgb/font/led/%.rgb : jpg/font/led/%.jpg
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh $<
	mv $(subst .jpg,.rgb,$<) $(@)

rgb/font/led_90/%.rgb : jpg/font/led_90/%.jpg
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh $<
	mv $(subst .jpg,.rgb,$<) $(@)

rgb/icons/%.rgb : tif/icons/%.tif
	$(TOOLS_DIR)/scripts/bg_black.sh $< tmpbg.tif
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh tmpbg.tif
	mv tmpbg.rgb $(subst gif/,tif/,$(@))

#rgb/icons/%.gif : tif/icons/%.tif
#	$(TOOLS_DIR)/scripts/bg_transparent.sh $< $@
#	mv $(subst gif/,tif/,$(@)) rgb/icons/

rgb/game/%.rgb : tif/game/%.tif
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh $<
	mv $(subst rgb/,tif/,$(@)) rgb/game/

rgb/game/%.rgb : tif/game/%.jpg
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh $<
	mv $(subst rgb/,tif/,$(@)) rgb/game/

rgb/flags/%.rgb : tif/flags/%.tif
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh $<
	mv $(subst rgb/,tif/,$(@)) rgb/flags/

rgb/%.rgb : jpg/%.jpg
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh $<
	mv $(subst rgb/,jpg/,$(@)) rgb/images

rgb/images/%.rgb : tif/images/%.tif
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh $<
	mv $(subst rgb/,tif/,$(@)) rgb/images

# User-supplied images
#
# put your photos in photos_src and then run 'make photos' to make the
# rgb files.  photos must be 320x240, To facilitate scrolling, we have
# to reverse and rotate the image 90 degress, just like we do for the
# credits app.
#
photos/%.rgb: photos_src/%.tif
	convert $< -resize 320x240 -gravity center -background black -extent 320x240 -fill white -undercolor black -gravity southwest -rotate 90 -flop $(subst photos_src/,photos/,$<)
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh $(subst photos_src/,photos/,$<)
	rm $(subst photos_src/,photos/,$<)

photos/%.rgb: photos_src/%.jpg
	convert "$<" -resize 320x240 -gravity center -background black -extent 320x240 -fill white -undercolor black -gravity southwest -rotate 90 -flop "$(subst photos_src/,photos/,$<)"
	$(TOOLS_DIR)/scripts/convert_to_rgb.sh "$(subst photos_src/,photos/,$<)"
	rm "$(subst photos_src/,photos/,$<)"

photos_src/letters.tif: Makefile
	convert -compress lzw -size 240x320 -gravity center -background black -fill white -font CourierNew -pointsize 26 label:"$$(for i in $$(jot 26 1); do	\
	printf "%b=%2d%s" \\0$$(				\
		printf %o $$((64 + $$i))			\
		) "$$i" "$$(					\
			if [ $$(($$i % 3)) == 0 ]; then		\
				printf "\\\\n";			\
			else					\
				printf " ";			\
			fi)";					\
	done )" -rotate 270 photos_src/letters.tif

photos_src/cards.tif: cardgen.py Makefile
	convert -compress lzw -gravity center -background black -fill white -font CourierNew -size 240x320 caption:"$$(python cardgen.py)" -rotate 270 photos_src/cards.tif
# User supplied photos if any.
photos: tools_dep $(addprefix photos/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard photos_src/*.tif))))) $(addprefix photos/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard photos_src/*.jpg))))) photos/letters.rgb photos/cards.rgb


# the credits image, if needed
tif/images/credits.tif: tif/images/credits.tif.orig
	convert $< -rotate 90 -flop tif/images/credits.tif

# Sounds
dac/%.snd: dac/%.mp3
	$(TOOLS_DIR)/scripts/sndmp3toraw.sh $<

dac/%.snd: dac/%.wav
	$(TOOLS_DIR)/scripts/sndmp3toraw.sh $<

dac/game/%.snd: dac/game/%.wav
	$(TOOLS_DIR)/scripts/sndmp3toraw.sh $<

# Videos
video/dabomb/%.vid: video_src/dabomb/%.mp4
	$(TOOLS_DIR)/scripts/encode_video.sh $< video/dabomb

video/misc/%.vid: video_src/misc/%.mp4
	$(TOOLS_DIR)/scripts/encode_video.sh $< video/misc

video/civildef/%.vid: video_src/civildef/%.mp4
	$(TOOLS_DIR)/scripts/encode_video.sh $< video/civildef

# When possible, please use TIF images. Aliasing is a real issue on
# our display and higher quality input is better.
#
# images used by the system, app-fight, and the "LED" app.
#
# if you add subfolders in tif/ you must add a rule here or make
# will not build the subfolder.

images: dirs tools_dep photos \
        $(addprefix rgb/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard tif/*.tif))))) \
        $(addprefix rgb/images/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard tif/images/*.tif))))) \
        $(addprefix rgb/icons/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard tif/icons/*.tif))))) \
        $(addprefix rgb/game/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard tif/game/*.tif))))) \
        $(addprefix rgb/game/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard tif/game/*.jpg))))) \
        $(addprefix rgb/flags/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard tif/flags/*.tif))))) \
        $(addprefix rgb/doom/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard jpg/doom/*.jpg))))) \
        $(addprefix rgb/font/led/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard jpg/font/led/*.jpg))))) \
        $(addprefix rgb/font/led_90/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard jpg/font/led_90/*.jpg))))) \
        $(addprefix rgb/, $(notdir  $(addsuffix .rgb, $(basename $(wildcard jpg/*.jpg)))))

# When possible please use .wav files as source material. MP3s already
# have enough compression and loss.

sounds: tools_dep $(addprefix dac/, $(notdir  $(addsuffix .snd, $(basename $(wildcard dac/*.wav dac/*.mp3))))) \
	          $(addprefix dac/game/, $(notdir  $(addsuffix .snd, $(basename $(wildcard dac/game/*.wav dac/game/*.mp3)))))

video_misc: tools_dep $(addprefix video/misc/, $(notdir  $(addsuffix .vid, $(basename $(wildcard video_src/misc/*.mp4)))))
video_dabomb: tools_dep $(addprefix video/dabomb/, $(notdir  $(addsuffix .vid, $(basename $(wildcard video_src/dabomb/*.mp4)))))
video_civildef: tools_dep $(addprefix video/civildef/, $(notdir  $(addsuffix .vid, $(basename $(wildcard video_src/civildef/*.mp4)))))

sdcard: dirs tools_dep images sounds video_misc video_dabomb video_civildef
	cp ../firmware/updater/updater.bin $(STAGING_DIR)
	-cp sdcard-readme.txt $(STAGING_DIR)/README.txt
	-cp rgb/images/*.rgb $(STAGING_DIR)/images
	-cp jpg/bomb.gif $(STAGING_DIR)/images
	-cp rgb/icons/*.rgb $(STAGING_DIR)/icons
	-cp rgb/flags/*.rgb $(STAGING_DIR)/flags
	-cp rgb/doom/*.rgb $(STAGING_DIR)/doom
	-cp rgb/font/led/*.rgb $(STAGING_DIR)/font/led
	-cp rgb/font/led_90/*.rgb $(STAGING_DIR)/font/led_90
	-cp ../../software/firmware/badge/build/badge.bin $(STAGING_DIR)
	-cp dac/*.snd $(STAGING_DIR)/sound
	-cp photos/*.rgb $(STAGING_DIR)/photos
	-cp rgb/game/*.rgb $(STAGING_DIR)/game
	-cp dac/game/*.snd $(STAGING_DIR)/game
	-cp video/misc/*.vid $(STAGING_DIR)/videos/misc
	-cp video/dabomb/*.vid $(STAGING_DIR)/videos/dabomb
	-cp video/civildef/*.vid $(STAGING_DIR)/videos/civildef
	-cp -R zgames/* $(STAGING_DIR)/stories
	@echo
	@echo 'sdcard built in $(STAGING_DIR)'
	@echo
	@echo 'build #'
	@strings $(STAGING_DIR)/badge.bin  | grep -1 gitrev | head -1
	du -kh $(STAGING_DIR)

# copy the card to the right folder on my osx box
osxsd:	sdcard
	@echo "Copying to $(VOLNAME)"
	rsync -crvv --delete $(STAGING_DIR)/ $(VOLNAME)/
	@sync

# copy only binaries and the updater to the card (reduces dev time
# when needed)
osxsdfw:	sdcard
	@echo "Updating binaries on $(VOLNAME)"
	@cp ../updater/updater.bin $(VOLNAME)/
	@cp $(STAGING_DIR)/badge.bin $(VOLNAME)/
	@sync

# cleanups
clean_images:
	-rm -fr rgb/*

dirs:
	-[ -d bin/ ] || mkdir -p bin/
	-[ -d photos/ ] || mkdir -p photos/
	-[ -d $(STAGING_DIR)/game ] || mkdir -p $(STAGING_DIR)/game
	-[ -d $(STAGING_DIR)/icons ] || mkdir -p $(STAGING_DIR)/icons
	-[ -d $(STAGING_DIR)/images ] || mkdir -p $(STAGING_DIR)/images
	-[ -d $(STAGING_DIR)/photos ] || mkdir -p $(STAGING_DIR)/photos
	-[ -d $(STAGING_DIR)/sound ] || mkdir -p $(STAGING_DIR)/sound
	-[ -d $(STAGING_DIR)/videos ] || mkdir -p $(STAGING_DIR)/videos
	-[ -d $(STAGING_DIR)/videos/misc ] || mkdir -p $(STAGING_DIR)/videos/misc
	-[ -d $(STAGING_DIR)/videos/dabomb ] || mkdir -p $(STAGING_DIR)/videos/dabomb
	-[ -d $(STAGING_DIR)/videos/civildef ] || mkdir -p $(STAGING_DIR)/videos/civildef
	-[ -d $(STAGING_DIR)/flags ] || mkdir -p $(STAGING_DIR)/flags
	-[ -d $(STAGING_DIR)/doom ] || mkdir -p $(STAGING_DIR)/doom
	-[ -d $(STAGING_DIR)/font/led ] || mkdir -p $(STAGING_DIR)/font/led
	-[ -d $(STAGING_DIR)/font/led_90 ] || mkdir -p $(STAGING_DIR)/font/led_90
	-[ -d $(STAGING_DIR)/stories ] || mkdir -p $(STAGING_DIR)/stories
	-[ -d rgb/icons ] || mkdir -p rgb/images
	-[ -d rgb/icons ] || mkdir -p rgb/icons
	-[ -d rgb/flags ] || mkdir -p rgb/flags
	-[ -d rgb/game ] || mkdir -p rgb/game
	-[ -d rgb/doom ] || mkdir -p rgb/doom
	-[ -d rgb/font/led ] || mkdir -p rgb/font/led
	-[ -d rgb/font/led_90 ] || mkdir -p rgb/font/led_90
	-[ -d saves ] || mkdir -p saves
	-[ -d video ] || mkdir -p video
	-[ -d video/misc ] || mkdir -p video/misc
	-[ -d video/dabomb ] || mkdir -p video/dabomb
	-[ -d video/civildef ] || mkdir -p video/civildef
cleansd:
	@if [ -d "$(STAGING_DIR)" ]; then rm -rf $(STAGING_DIR); fi;
	@if [ -d "rgb" ]; then rm -rf rgb; fi;

# remove tools, sounds, images, and video
clean: clean_images
	$(MAKE) -C $(TOOLS_DIR) clean
	-rm -rf bin/
	-rm -f dac/*.snd
	-rm -f dac/game/*.snd
	-rm -rf video/*
	-rm -fr $(STAGING_DIR)/*
	-rm -f photos/*
	-rm -f tif/mirrored/*
	-rm -fr sdcard/*
