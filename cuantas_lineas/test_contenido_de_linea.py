from cuantas_lineas import contenido_de_linea

singleline = "//"
multiline_open = "/*"
multiline_close = "*/"

#Una lista de casos de prueba:
#Cada elemento es una tupla con:
#- una línea de código
#- resultado esperado sin multilinea abierto
#- resultado esperado con multilinea abierto
casos = [("i++; //hola",  (True,  True,  False), (False, True,  True )),
         ("// *//**/",    (False, True,  False), (False, True,  False)),
         ("// *//**",     (False, True,  False), (False, True,  True )),
         ("/* // */",     (False, True,  False), (False, True,  False)),
         ("hola // */",   (True,  True,  False), (False, True,  False)),
         ("hola // *",    (True,  True,  False), (False, True,  True )),
         ("    hola",     (True,  False, False), (False, True,  True )),
         ("hola // ",     (True,  False, False), (False, True,  True )),
        #("hola */ i++;", (Exception("")      ), (True,  True,  False)),
         ("/**/ i++; //", (True,  False, False), (True,  True,  False)),
         ("/*",           (False, False, True ), (False, True,  True )),
         ("\t",           (False, False, False), (False, False, True ))]

#Probar con cada caso:
for linea, expected1, expected2 in casos:
    result = contenido_de_linea(linea, False, singleline, multiline_open, multiline_close)
    if result != expected1:
        raise Exception(f"Sin multiline abierto se esperaba obtener {expected1}, pero el resultado fue {result}.\nEn la línea:\n{linea}")
    
    result = contenido_de_linea(linea, True, singleline, multiline_open, multiline_close)
    if result != expected2:
        raise Exception(f"Con multiline abierto se esperaba obtener {expected2}, pero el resultado fue {result}.\nEn la línea:\n{linea}")

print("Todos los casos están OK.")
        