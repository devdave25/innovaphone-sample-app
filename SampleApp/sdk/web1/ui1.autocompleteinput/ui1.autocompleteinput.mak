
WEBSRC += \
	web/ui1.autocompleteinput/innovaphone.ui1.autocompleteinput.js

$(OUTDIR)/obj/ui1.autocompleteinput_httpdata.cpp: $(IP_SRC)/web1/ui1.autocompleteinput/ui1.autocompleteinput.mak $(IP_SRC)/web1/ui1.autocompleteinput/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/ui1.autocompleteinput_httpdata.cpp \
		ui1.autocompleteinput/innovaphone.ui1.autocompleteinput.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD

COMMONOBJS += $(OUTDIR)/obj/ui1.autocompleteinput_httpdata.o
$(OUTDIR)/obj/ui1.autocompleteinput_httpdata.o: $(OUTDIR)/obj/ui1.autocompleteinput_httpdata.cpp
