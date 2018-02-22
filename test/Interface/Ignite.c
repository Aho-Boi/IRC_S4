/* J'etais parti sur du GTK simple de base mais j'ai change pour Glade parce que GTK c'est du vomi.
Problemes : 
-Est-ce qu'il faut bien utiliser TextEntry et TextView
-Y'a pas beaucoup de lignes mais wallah j'ai taffé
-Y'a quasi rien sur l'interface mais en vrai la doc est degueu, je suis pas juste nul
-J'avoue je suis nul me tape pas chef, je te jure que j'ai taffé 
*/



#include <gtk/gtk.h>

const gchar *empty_text = " ";

int
main(int argc, char *argv [])
{
  GtkWidget *main = NULL;
  GtkBuilder *builder = NULL;
  GError *error = NULL;
  gchar *filename = NULL;
  GtkEntry *textEntry = NULL;
  
  
  
  gtk_init(&argc, &argv);
  
  builder = gtk_builder_new();
  
  /*On cherche le fichier .glade puis on build l'interface */
  filename =  g_build_filename ("First.glade", NULL);
  gtk_builder_add_from_file (builder, filename, &error);
  
  
  /* Gestion d'erreur si le fichier n'a pas bien build */
  
  g_free (filename);
  if (error)
    {
      gint code = error->code;
      g_printerr("%s\n", error->message);
      g_error_free (error);
      return code;
    }
  
  /* Récupération du pointeur sur Main */
  main = GTK_WIDGET(gtk_builder_get_object (builder, "Main"));
  
  g_signal_connect (G_OBJECT (main), "destroy", (GCallback)gtk_main_quit, NULL);
  
  g_signal_connect (G_OBJECT (send), "clicked", (GCallback)on_Send_clicked(textEntry)));


  /* Affichage du Main et de tous ses widgets */ 
  gtk_widget_show_all(main);

  gtk_main();

  return 0;
  }


/*Action quand on clique sur le bouton Send*/
void on_Send_clicked(GtkEntry *entry){
  const gchar *text_in_entry = gtk_entry_get_text(entry); // Doit recuperer le texte dans TextEntry
  
  gtk_entry_set_text(entry, empty_text); //Efface ce qu'il y a dans le TextEntry
  
  /*Ensuite on insert dans TextView ce qu'on vient de recuperer dans *text_in_entry

   */
  
  free(text_in_entry);
  
}

