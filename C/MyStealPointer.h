
/* Este macro recibe un pointer p, lo setea en NULL, y devuelve el
   valor que p tenía previamente.
   El valor devueto tiene el mismo tipo que p.

   La idea es que esto transfiere la propiedad de p de la variable
   referenciada al statement donde se llama al macro: "roba" el
   pointer.

   Esto está robado de GLib, pero la implementación es distinta.
   https://gitlab.gnome.org/GNOME/glib/-/blob/main/glib/gmem.h
*/

#define steal_pointer(p) ({   \
   typeof(p) temp = (p);      \
   (p) = NULL;                \
   temp;                      \
})
