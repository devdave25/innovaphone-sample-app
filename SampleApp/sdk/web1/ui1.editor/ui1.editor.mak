
WEBSRC += \
	web/ui1.editor/innovaphone.ui1.editor.js \
	web/ui1.editor/ui1.editor.png

$(OUTDIR)/obj/ui1.editor_httpdata.cpp: $(IP_SRC)/web1/ui1.editor/ui1.editor.mak $(IP_SRC)/web1/ui1.editor/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/ui1.editor_httpdata.cpp \
		ui1.editor/innovaphone.ui1.editor.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD \
        ui1.editor/ui1.editor.png,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD \

COMMONOBJS += $(OUTDIR)/obj/ui1.editor_httpdata.o
$(OUTDIR)/obj/ui1.editor_httpdata.o: $(OUTDIR)/obj/ui1.editor_httpdata.cpp
