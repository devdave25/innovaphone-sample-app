
APPWEBPATH = SampleApp/apps

STARTHTMLS += \
	$(APPWEBPATH)/reinforce-sampleappadmin.htm \
	$(APPWEBPATH)/reinforce-sampleapp.htm \
	$(APPWEBPATH)/contact-exporter.htm

APPWEBSRC_NOZIP += \
	$(APPWEBPATH)/reinforce-sampleappadmin.png \
	$(APPWEBPATH)/reinforce-sampleapp.png

APPWEBSRC_ZIP += \
	$(APPWEBPATH)/reinforce-sampleapp.js \
	$(APPWEBPATH)/reinforce-sampleappadmin.js \
	$(APPWEBPATH)/reinforce-sampleapp.css \
	$(APPWEBPATH)/reinforce-sampleapptexts.js \
	$(APPWEBPATH)/reinforce.sampleappmanager.js \
	$(APPWEBPATH)/reinforce.sampleappmanager.css \
	$(APPWEBPATH)/reinforce.sampleappmanagertexts.js \
	$(APPWEBPATH)/contact-exporter.js \
	$(APPWEBPATH)/contact-exporter.css \

APPWEBSRC = $(APPWEBSRC_ZIP) $(APPWEBSRC_NOZIP)

$(OUTDIR)/obj/apps_start.cpp: $(STARTHTMLS) $(OUTDIR)/obj/innovaphone.manifest
		$(IP_SRC)/exe/httpfiles -k -d $(OUTDIR)/obj -t $(OUTDIR) -o $(OUTDIR)/obj/apps_start.cpp \
	-s 0 $(subst $(APPWEBPATH)/,,$(STARTHTMLS))

$(OUTDIR)/obj/apps.cpp: $(APPWEBSRC)
		$(IP_SRC)/exe/httpfiles -k -d $(APPWEBPATH) -t $(OUTDIR) -o $(OUTDIR)/obj/apps.cpp \
	-s 0,HTTP_GZIP $(subst $(APPWEBPATH)/,,$(APPWEBSRC_ZIP)) \
	-s 0 $(subst $(APPWEBPATH)/,,$(APPWEBSRC_NOZIP))

APP_OBJS += $(OUTDIR)/obj/apps_start.o
$(OUTDIR)/obj/apps_start.o: $(OUTDIR)/obj/apps_start.cpp
APP_OBJS += $(OUTDIR)/obj/apps.o
$(OUTDIR)/obj/apps.o: $(OUTDIR)/obj/apps.cpp
