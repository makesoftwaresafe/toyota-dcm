??          ?   %   ?      `  ?  a  ?  4  !   ?  !   ?  /     <   6  2   s  $   ?     ?  %   ?  *   
  +   5  .   a     ?     ?     ?     ?  "   ?     	     2	  3   @	  
  t	     
     ?
     ?
     ?
  (  ?
  ?    ?  ?  $   ?  %   ?  5   ?  E     4   Z  )   ?     ?  4   ?  3     3   9  ;   m     ?  #   ?  !   ?       .   %     T     k  /   ~  *  ?     ?     ?          5           
                                                                                        	                           -n, --name=name         get the named extended attribute value
  -d, --dump              get all extended attribute values
  -e, --encoding=...      encode values (as 'text', 'hex' or 'base64')
      --match=pattern     only get attributes with names matching pattern
      --only-values       print the bare values only
  -h, --no-dereference    do not dereference symbolic links
      --absolute-names    don't strip leading '/' in pathnames
  -R, --recursive         recurse into subdirectories
  -L, --logical           logical walk, follow symbolic links
  -P  --physical          physical walk, do not follow symbolic links
      --version           print version and exit
      --help              this help text
   -n, --name=name         set the value of the named extended attribute
  -x, --remove=name       remove the named extended attribute
  -v, --value=value       use value as the attribute value
  -h, --no-dereference    do not dereference symbolic links
      --restore=file      restore extended attributes
      --version           print version and exit
      --help              this help text
 %s %s -- get extended attributes
 %s %s -- set extended attributes
 %s: %s: No filename found in line %d, aborting
 %s: No filename found inline %d of standard input, aborting
 %s: Removing leading '/' from absolute path names
 %s: invalid regular expression "%s"
 -V only allowed with -s
 A filename to operate on is required
 At least one of -s, -g, or -r is required
 Attribute "%s" had a %d byte value for %s:
 Attribute "%s" set to a %d byte value for %s:
 Could not get "%s" for %s
 Could not remove "%s" for %s
 Could not set "%s" for %s
 No such attribute Only one of -s, -g, or -r allowed
 Unrecognized option: %c
 Usage: %s %s
 Usage: %s %s
Try `%s --help' for more information.
 Usage: %s [-LRq] -s attrname [-V attrvalue] pathname  # set value
       %s [-LRq] -g attrname pathname                 # get value
       %s [-LRq] -r attrname pathname                 # remove attr
      -s reads a value from stdin and -g writes a value to stdout
 getting attribute %s of %s listing attributes of %s setting attribute %s for %s setting attributes for %s Project-Id-Version: attr-2.2.0
POT-Creation-Date: 2002-12-02 00:45+0100
PO-Revision-Date: 2003-01-23 01:31+0100
Last-Translator: Andreas Grünbacher <a.gruenbacher@computer.org>
Language-Team:  <de@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
   -n, --name=name         Das angegebene erweiterte Attribut lesen
  -d, --dump              Alle erweiterten Attribute lesen
  -e, --encoding=...      Wert codieren (als 'text', 'hex' oder 'base64')
      --match=muster      Nur Attribute, die mit muster übereinstimmen
      --only-values       Die Attributwerte ohne Codierung ausgeben
  -h, --no-dereference    Symbolische Links nicht dereferenzieren
      --absolute-names    Führende '/' in Pfadnamen nicht entfernen
  -R, --recursive         In Unterverzeichnisse wechseln
  -L, --logical           Alle symbolischen Links verfolgen
  -P  --physical          Symbolische Links nicht verfolgen
      --version           Die Version ausgeben
      --help              Diese Hilfe
   -n, --name=name         Name des Attributs, das gesetzt werden soll
  -x, --remove=name       Entfernt das angegebene erweiterte Attribut
  -v, --value=wert        Wert für das erweiterte Attribut
  -h, --no-dereference    Symbolische Links nicht dereferenzieren
      --restore=datei     Erweiterte Attribute wiederhestellen
      --version           Die Version ausgeben
      --help              Diese Hilfe
 %s %s -- erweiterte Attribute lesen
 %s %s -- Erweiterte Attribute setzen
 %s: %s: Kein Dateiname in Zeile %d gefunden, Abbruch
 %s: Kein Dateiname in Zeile %d der Standardeingabe gefunden, Abbruch
 %s: Entferne führenden '/' von absoluten Pfadnamen
 %s: ungültiger regulärer Ausdruck "%s"
 -V nur mit -s erlaubt
 Der Name der zu verwendenden Datei ist erforderlich
 Eine der Optionen -s, -g, oder -r ist erforderlich
 Attribut "%1$s" von %3$s hat einen %2$d-Byte-Wert:
 Attribut "%1$s" von %3$s auf einen %2$d-Byte-Wert gesetzt:
 Konnte "%s" von %s nicht lesen
 Konnte "%s" von %s nicht entfernen
 Konnte "%s" für %s nicht setzen
 Kein solches Attribut Nur eine der Optionen -s, -g, oder -r erlaubt
 Unbekannte Option: %c
 Verwendung: %s %s
 Weiterführende Informationen mit `%s --help'.
 Verwendung: %s [-LRq] -s attrname [-V attrvalue] pfadname  # Wert setzen
            %s [-LRq] -g attrname pfadname                 # Wert lesen
            %s [-LRq] -r attrname pfadname                 # Wert entfernen
            -s liest einen Wert von stdin, -g schreibt einen Wert auf stdout
 Lesen von Attribut %s von %s Auslisten von Attributen von %s Setzen von Attribut %s für %s Setzen von Attributen für %s 