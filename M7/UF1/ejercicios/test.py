#!/usr/bin/env python

#Importa libreria
from gi.repository import Gtk
import time

def find (node, id):
    if node.XXX() == id: return node
    for child in node.get_children():
            ret = find(child, id)
            if ret: return ret
            return None
     
def loadMain(arg1 = None, arg2 = None):
    #Constructor
    builder = Gtk.Builder()
    #Expande glade
    builder.add_from_file("PrimeraInterfaz.glade")
    #coge ventana
    window = builder.get_object("Login")
    user = builder.get_object("Usuario")
    user.set_text("hola");
    window.connect("delete-event", Gtk.main_quit)
    window.show_all()
    btn_entrar=builder.get_object("Entrar")
    hora = builder.get_object("Hora")
    fecha = builder.get_object("Fecha")
    t=time.strftime('%H:%M:%S')
    d=time.strftime('%d/%m/%y')
    hora.set_text(t)
    fecha.set_text(d)
    #print window
    handlers = {
        "onDeleteWindow": Gtk.main_quit,
        "entrar": entrar
    }
     
    builder.connect_signals(handlers)

def entrar(self):
    #Ir a OK
    #window.destroy(self.get_ancestor(Gtk.button),self)
    builder = Gtk.Builder()
    builder.add_from_file("PrimeraInterfaz.glade")
    window = self.get_ancestor(Gtk.Window)
    #print window.get_child().get_children("Usuario");
    #user = builder.get_object("Usuario");
    #print user.get_text();

    container = window.get_child();
#    def find_child_classes(container, cls):
    entrys = [widget for widget in container.get_children() if (widget, Gtk.Entry)]
    print entrys[1].get_name();
    
    #print window
    #print(window.child_get(widget,"Usuario"));
    window.destroy();
    window = builder.get_object("OK");
    #window.connect("delete-event", Gtk.main_quit)
    window.connect("delete-event", loadMain)
    window.show_all()
    print(self);
    #print("Has clicado")
     
      
       
#class Handler:
#    def onDeleteWindow(self, *args):
#        Gtk.main_quit(*args)
#    def onButtonPressed(self, button):
#        print("Hello World!")

#btn_entrar.connect("clicked",clicado)
 
loadMain();
Gtk.main();
