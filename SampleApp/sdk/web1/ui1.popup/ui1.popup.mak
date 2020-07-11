
WEBSRC += \
	web/ui1.popup/innovaphone.ui1.popup.js

$(OUTDIR)/obj/ui1.popup_httpdata.cpp: $(IP_SRC)/web1/ui1.popup/ui1.popup.mak $(IP_SRC)/web1/ui1.popup/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/ui1.popup_httpdata.cpp \
		ui1.popup/innovaphone.ui1.popup.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD

COMMONOBJS += $(OUTDIR)/obj/ui1.popup_httpdata.o
$(OUTDIR)/obj/ui1.popup_httpdata.o: $(OUTDIR)/obj/ui1.popup_httpdata.cpp
