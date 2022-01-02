

// Milad Cheraghi

//tak.cheraghi@gmail.com

// ELF Parser


#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <elf.h>
#include <math.h>
#include <stdlib.h>

#if defined(__LP64__)
#define ElfW(type) Elf64_ ## type
#else
#define ElfW(type) Elf32_ ## type
#endif



ElfW(Ehdr) read_elf_header(const char* elfFile) {
  // Either Elf64_Ehdr or Elf32_Ehdr depending on architecture.
	ElfW(Ehdr) header;

	FILE* file = fopen(elfFile, "rb");
	if(file) {
    // read the header
		fread(&header, sizeof(header), 1, file);
    		
    // finally close the file
		fclose(file);
	}
	return header;
}




GtkWidget *window;
GtkLabel *FileFormat_lbl;
GtkLabel *Magic_lbl;
GtkLabel *Format_lbl;
GtkLabel *Archituctur_lbl;
GtkLabel *LSBMSB_lbl;
GtkLabel *VERSION_lbl;
GtkLabel *OSABI_lbl;
GtkLabel *TYPE_lbl;
GtkLabel *MACHINE_lbl;


int main(int argc,char *argv[]){



	GtkBuilder *builder;
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "MainUI.glade", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "MainPage"));
	
	Magic_lbl = GTK_LABEL(gtk_builder_get_object(builder, "Magic_lbl"));
	Format_lbl = GTK_LABEL(gtk_builder_get_object(builder, "Format_lbl"));
	Archituctur_lbl = GTK_LABEL(gtk_builder_get_object(builder, "Archituctur_lbl"));
	LSBMSB_lbl = GTK_LABEL(gtk_builder_get_object(builder, "LSBMSB_lbl"));
	VERSION_lbl = GTK_LABEL(gtk_builder_get_object(builder, "VERSION_lbl"));
	OSABI_lbl = GTK_LABEL(gtk_builder_get_object(builder, "OSABI_lbl"));
	TYPE_lbl = GTK_LABEL(gtk_builder_get_object(builder, "TYPE_lbl"));
	MACHINE_lbl = GTK_LABEL(gtk_builder_get_object(builder, "MACHINE_lbl"));
	
	gtk_builder_connect_signals(builder,NULL);
	g_object_unref(builder);

	gtk_widget_show_all(window);
	gtk_main();



	
	return 0;
}

void exit_app(){
	printf("Exit Button Clicked!");
	gtk_main_quit();
}

void SelectELFclicked_btn(){
	char str[7];
	char str1[20];
	char str2[10];
	char str3[10];
	char str4[10];
	char str5[4];
	char str6[10];
	char str7[100];
	ElfW(Ehdr) eh = read_elf_header("ELFparser");
	printf("Button Clicked!");
	sprintf(str,"%hhu",eh.e_ident[0] );
	sprintf(str1,"%c%c%c",eh.e_ident[1],eh.e_ident[2],eh.e_ident[3]);
	sprintf(str2,"%hhu",eh.e_ident[4] );
	sprintf(str3,"%hhu",eh.e_ident[5] );
	sprintf(str4,"%hhu",eh.e_ident[6] );
	sprintf(str5,"%hhu",eh.e_ident[7] );
	sprintf(str6,"%hhu",eh.e_type );
	sprintf(str7,"%d", (int)sizeof eh.e_machine );
	
	gtk_label_set_text(Magic_lbl,str);
	gtk_label_set_text(Format_lbl,str1);
	gtk_label_set_text(Archituctur_lbl,str2);
	gtk_label_set_text(LSBMSB_lbl,str3);
	gtk_label_set_text(VERSION_lbl,str4);
	gtk_label_set_text(OSABI_lbl,str5);
	gtk_label_set_text(TYPE_lbl,str6);
	gtk_label_set_text(MACHINE_lbl,str7);
}


