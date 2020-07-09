include SampleApp/apps/apps.mak

APP_OBJS += $(OUTDIR)/obj/SampleApp.o
$(OUTDIR)/obj/SampleApp.o: SampleApp/SampleApp.cpp $(OUTDIR)/SampleApp/SampleApp.png

APP_OBJS += $(OUTDIR)/obj/SampleApp_tasks.o
$(OUTDIR)/obj/SampleApp_tasks.o: SampleApp/SampleApp_tasks.cpp

$(OUTDIR)/SampleApp/SampleApp.png: SampleApp/SampleApp.png
	copy SampleApp\SampleApp.png $(OUTDIR)\SampleApp\SampleApp.png
