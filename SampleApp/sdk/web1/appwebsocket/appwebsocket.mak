
WEBSRC += \
	web/appwebsocket/innovaphone.appwebsocket.Connection.js

$(OUTDIR)/obj/appwebsocket_httpdata.cpp: $(IP_SRC)/web1/appwebsocket/appwebsocket.mak $(IP_SRC)/web1/appwebsocket/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/appwebsocket_httpdata.cpp \
		appwebsocket/innovaphone.appwebsocket.Connection.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD

COMMONOBJS += $(OUTDIR)/obj/appwebsocket_httpdata.o
$(OUTDIR)/obj/appwebsocket_httpdata.o: $(OUTDIR)/obj/appwebsocket_httpdata.cpp
