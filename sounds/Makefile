#!/usr/bin/make -f

all: download

clean:
	rm -f sf2/*

download: \
	sf2/AirFont320/instrument.sf2 \
	sf2/AVL_Drumkits_Perc/instrument.sf2 \
	sf2/Black_Pearl_4A/instrument.sf2 \
	sf2/Black_Pearl_4B/instrument.sf2 \
	sf2/Black_Pearl_5/instrument.sf2 \
	sf2/Red_Zeppelin_4/instrument.sf2 \
	sf2/Red_Zeppelin_5/instrument.sf2 \
	sf2/FluidGM/instrument.sf2 \
	sf2/FluidBass/instrument.sf2 \
	sf2/FluidBrass/instrument.sf2 \
	sf2/FluidChromPerc/instrument.sf2 \
	sf2/FluidDrums/instrument.sf2 \
	sf2/FluidEnsemble/instrument.sf2 \
	sf2/FluidEthnic/instrument.sf2 \
	sf2/FluidGuitars/instrument.sf2 \
	sf2/FluidOrgans/instrument.sf2 \
	sf2/FluidPercussion/instrument.sf2 \
	sf2/FluidPianos/instrument.sf2 \
	sf2/FluidPipes/instrument.sf2 \
	sf2/FluidReeds/instrument.sf2 \
	sf2/FluidSoundFX/instrument.sf2 \
	sf2/FluidStrings/instrument.sf2 \
	sf2/FluidSynthFX/instrument.sf2 \
	sf2/FluidSynthLeads/instrument.sf2 \
	sf2/FluidSynthPads/instrument.sf2

	
sf2/AirFont320/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/AirFont320 && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/airfont_a340u.tar.7z && \
		7z x airfont_a340u.tar.7z && \
		7z x airfont_a340u.tar && \
		mv airfont_a340u/* . && \
		mv airfont_a320u.sf2 instrument.sf2 && \
		mv readme README && \
		rmdir airfont_a340u)

sf2/AVL_Drumkits_Perc/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/AVL_Drumkits_Perc && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/AVL-Drumkits-1.1-SF2-splitted/AVL_Drumkits_Perc_1.1.tar.7z && \
		7z x AVL_Drumkits_Perc_1.1.tar.7z && \
		7z x AVL_Drumkits_Perc_1.1.tar && \
		mv AVL_Drumkits_Perc_1.1/* . && \
		mv AVL_Drumkits_Perc_1.1.sf2 instrument.sf2 && \
		mv 'AVL-Drumkits CC-BY-SA License.pdf' License.pdf && \
		rmdir AVL_Drumkits_Perc_1.1)

sf2/Black_Pearl_4A/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/Black_Pearl_4A && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/AVL-Drumkits-1.1-SF2-splitted/Black_Pearl_4A-1.1.tar.7z && \
		7z x Black_Pearl_4A-1.1.tar.7z && \
		7z x Black_Pearl_4A-1.1.tar && \
		mv Black_Pearl_4A-1.1/* . && \
		mv Black_Pearl_4A-1.1.sf2 instrument.sf2 && \
		mv 'AVL-Drumkits CC-BY-SA License.pdf' License.pdf && \
		rmdir Black_Pearl_4A-1.1)

sf2/Black_Pearl_4B/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/Black_Pearl_4B && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/AVL-Drumkits-1.1-SF2-splitted/Black_Pearl_4B-1.1.tar.7z && \
		7z x Black_Pearl_4B-1.1.tar.7z && \
		7z x Black_Pearl_4B-1.1.tar && \
		mv Black_Pearl_4B-1.1/* . && \
		mv Black_Pearl_4B-1.1.sf2 instrument.sf2 && \
		mv 'AVL-Drumkits CC-BY-SA License.pdf' License.pdf && \
		rmdir Black_Pearl_4B-1.1)

sf2/Black_Pearl_5/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/Black_Pearl_5 && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/AVL-Drumkits-1.1-SF2-splitted/Black_Pearl_5-1.1.tar.7z && \
		7z x Black_Pearl_5-1.1.tar.7z && \
		7z x Black_Pearl_5-1.1.tar && \
		mv Black_Pearl_5-1.1/* . && \
		mv Black_Pearl_5-1.1.sf2 instrument.sf2 && \
		mv 'AVL-Drumkits CC-BY-SA License.pdf' License.pdf && \
		rmdir Black_Pearl_5-1.1)

sf2/Red_Zeppelin_4/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/Red_Zeppelin_4 && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/AVL-Drumkits-1.1-SF2-splitted/Red_Zeppelin_4-1.1.tar.7z && \
		7z x Red_Zeppelin_4-1.1.tar.7z && \
		7z x Red_Zeppelin_4-1.1.tar && \
		mv Red_Zeppelin_4-1.1/* . && \
		mv Red_Zeppelin_4-1.1.sf2 instrument.sf2 && \
		mv 'AVL-Drumkits CC-BY-SA License.pdf' License.pdf && \
		rmdir Red_Zeppelin_4-1.1)

sf2/Red_Zeppelin_5/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/Red_Zeppelin_5 && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/AVL-Drumkits-1.1-SF2-splitted/Red_Zeppelin_5-1.1.tar.7z && \
		7z x Red_Zeppelin_5-1.1.tar.7z && \
		7z x Red_Zeppelin_5-1.1.tar && \
		mv Red_Zeppelin_5-1.1/* . && \
		mv Red_Zeppelin_5-1.1.sf2 instrument.sf2 && \
		mv 'AVL-Drumkits CC-BY-SA License.pdf' License.pdf && \
		rmdir Red_Zeppelin_5-1.1)

sf2/FluidGM/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidGM && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3.tar.7z && \
		7z x fluidr3.tar.7z && \
		7z x fluidr3.tar && \
		mv fluidr3/* . && \
		mv fluidr3gm.sf2 instrument.sf2 && \
		mv readme README && \
		rmdir fluidr3)

sf2/FluidBass/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidBass && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_bass.sf2.tar.7z && \
		7z x fluidr3gm_bass.sf2.tar.7z && \
		7z x fluidr3gm_bass.sf2.tar && \
		mv fluidr3gm_bass.sf2 instrument.sf2)

sf2/FluidBrass/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidBrass && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_brass.sf2.tar.7z && \
		7z x fluidr3gm_brass.sf2.tar.7z && \
		7z x fluidr3gm_brass.sf2.tar && \
		mv fluidr3gm_brass.sf2 instrument.sf2)

sf2/FluidChromPerc/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidChromPerc && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_chromaticpercussion.sf2.tar.7z && \
		7z x fluidr3gm_chromaticpercussion.sf2.tar.7z && \
		7z x fluidr3gm_chromaticpercussion.sf2.tar && \
		mv fluidr3gm_chromaticpercussion.sf2 instrument.sf2)

sf2/FluidDrums/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidDrums && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_drums.sf2.tar.7z && \
		7z x fluidr3gm_drums.sf2.tar.7z && \
		7z x fluidr3gm_drums.sf2.tar && \
		mv fluidr3gm_drums.sf2 instrument.sf2)

sf2/FluidEnsemble/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidEnsemble && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_ensemble.sf2.tar.7z && \
		7z x fluidr3gm_ensemble.sf2.tar.7z && \
		7z x fluidr3gm_ensemble.sf2.tar && \
		mv fluidr3gm_ensemble.sf2 instrument.sf2)

sf2/FluidEthnic/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidEthnic && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_ethnic.sf2.tar.7z && \
		7z x fluidr3gm_ethnic.sf2.tar.7z && \
		7z x fluidr3gm_ethnic.sf2.tar && \
		mv fluidr3gm_ethnic.sf2 instrument.sf2)

sf2/FluidGuitars/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidGuitars && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_guitar.sf2.tar.7z && \
		7z x fluidr3gm_guitar.sf2.tar.7z && \
		7z x fluidr3gm_guitar.sf2.tar && \
		mv fluidr3gm_guitar.sf2 instrument.sf2)

sf2/FluidOrgans/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidOrgans && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_organ.sf2.tar.7z && \
		7z x fluidr3gm_organ.sf2.tar.7z && \
		7z x fluidr3gm_organ.sf2.tar && \
		mv fluidr3gm_organ.sf2 instrument.sf2)

sf2/FluidPercussion/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidPercussion && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_percussive.sf2.tar.7z && \
		7z x fluidr3gm_percussive.sf2.tar.7z && \
		7z x fluidr3gm_percussive.sf2.tar && \
		mv fluidr3gm_percussive.sf2 instrument.sf2)

sf2/FluidPianos/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidPianos && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_piano.sf2.tar.7z && \
		7z x fluidr3gm_piano.sf2.tar.7z && \
		7z x fluidr3gm_piano.sf2.tar && \
		mv fluidr3gm_piano.sf2 instrument.sf2)

sf2/FluidPipes/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidPipes && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_pipe.sf2.tar.7z && \
		7z x fluidr3gm_pipe.sf2.tar.7z && \
		7z x fluidr3gm_pipe.sf2.tar && \
		mv fluidr3gm_pipe.sf2 instrument.sf2)

sf2/FluidReeds/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidReeds && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_reed.sf2.tar.7z && \
		7z x fluidr3gm_reed.sf2.tar.7z && \
		7z x fluidr3gm_reed.sf2.tar && \
		mv fluidr3gm_reed.sf2 instrument.sf2)

sf2/FluidSoundFX/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidSoundFX && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_soundeffects.sf2.tar.7z && \
		7z x fluidr3gm_soundeffects.sf2.tar.7z && \
		7z x fluidr3gm_soundeffects.sf2.tar && \
		mv fluidr3gm_soundeffects.sf2 instrument.sf2)

sf2/FluidStrings/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidStrings && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_strings.sf2.tar.7z && \
		7z x fluidr3gm_strings.sf2.tar.7z && \
		7z x fluidr3gm_strings.sf2.tar && \
		mv fluidr3gm_strings.sf2 instrument.sf2)

sf2/FluidSynthFX/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidSynthFX && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_syntheffects.sf2.tar.7z && \
		7z x fluidr3gm_syntheffects.sf2.tar.7z && \
		7z x fluidr3gm_syntheffects.sf2.tar && \
		mv fluidr3gm_syntheffects.sf2 instrument.sf2)

sf2/FluidSynthLeads/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidSynthLeads && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_synthlead.sf2.tar.7z && \
		7z x fluidr3gm_synthlead.sf2.tar.7z && \
		7z x fluidr3gm_synthlead.sf2.tar && \
		mv fluidr3gm_synthlead.sf2 instrument.sf2)

sf2/FluidSynthPads/instrument.sf2:
	-@mkdir -p $(shell dirname $@)
	(cd sf2/FluidSynthPads && \
		wget http://download.linuxaudio.org/musical-instrument-libraries/sf2/fluidr3-splitted/fluidr3gm_synthpad.sf2.tar.7z && \
		7z x fluidr3gm_synthpad.sf2.tar.7z && \
		7z x fluidr3gm_synthpad.sf2.tar && \
		mv fluidr3gm_synthpad.sf2 instrument.sf2)
