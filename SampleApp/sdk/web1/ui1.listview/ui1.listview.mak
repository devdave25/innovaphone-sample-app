
WEBSRC += \
	web/ui1.listview/innovaphone.ui1.listview.js \
	web/ui1.listview/arrow.png

$(OUTDIR)/obj/ui1.listview_httpdata.cpp: $(IP_SRC)/web1/ui1.listview/ui1.listview.mak $(IP_SRC)/web1/ui1.listview/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/ui1.listview_httpdata.cpp \
		ui1.listview/innovaphone.ui1.listview.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD \
		ui1.listview/arrow.png,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD

COMMONOBJS += $(OUTDIR)/obj/ui1.listview_httpdata.o
$(OUTDIR)/obj/ui1.listview_httpdata.o: $(OUTDIR)/obj/ui1.listview_httpdata.cpp
