
ifndef WEB_COM_INNOVAPHONE_AVATAR
WEB_COM_INNOVAPHONE_AVATAR = 1

WEBSRC += \
	web/com.innovaphone.avatar/com.innovaphone.avatar.js

$(OUTDIR)/obj/com_innovaphone_avatar_httpdata.cpp: $(IP_SRC)/web1/com.innovaphone.avatar/com.innovaphone.avatar.mak $(IP_SRC)/web1/com.innovaphone.avatar/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/com_innovaphone_avatar_httpdata.cpp \
		com.innovaphone.avatar/com.innovaphone.avatar.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD

COMMONOBJS += $(OUTDIR)/obj/com_innovaphone_avatar_httpdata.o
$(OUTDIR)/obj/com_innovaphone_avatar_httpdata.o: $(OUTDIR)/obj/com_innovaphone_avatar_httpdata.cpp

endif