# 🎯 Sistema de Reserva de Equipos para Actividades Recreativas (C++)

## 📌 Descripción  
Este proyecto implementa un sistema en **C++** que permite gestionar la **reserva de equipos para actividades recreativas**, tales como balones, bicicletas o implementos deportivos.  
El sistema administra la disponibilidad de los equipos, evita reservas duplicadas, permite cancelaciones, y maneja una **cola de espera** para asignar automáticamente un turno cuando un equipo reservado vuelve a estar disponible.  

---

## ⚙️ Funcionalidades principales  
- **Consultar equipos por categoría**  
  Visualiza los implementos disponibles en cada categoría (Fútbol, Natación, Voleibol, Baloncesto).  
  _(Solo muestra los nombres, sin estado)._  

- **Consultar disponibilidad de equipos**  
  Muestra todos los equipos junto con su **estado** (`Disponible` / `Reservado`).  

- **Reservar un equipo**  
  - El usuario ingresa su número de identificación.  
  - Selecciona la categoría y el equipo deseado.  
  - Si ya está reservado, el sistema ofrece unirse a la **cola de espera**.  

- **Consultar reservas realizadas**  
  El usuario puede consultar qué equipos tiene reservados ingresando su número de identificación.  

- **Cancelar una reserva**  
  - Permite cancelar una reserva activa.  
  - El equipo vuelve a estar **disponible**.  
  - Si existe una cola de espera, el primer usuario en la cola obtiene la reserva automáticamente.  

---

## 🗂️ Estructura del Proyecto  
El sistema se organiza en clases para una mejor modularidad:  

- **Equipo** → Representa un implemento deportivo con ID, nombre, categoría y estado.  
- **Reserva** → Administra la información de las reservas (usuario y equipo).  
- **SistemaReserva** → Contiene la lógica principal de gestión (consultas, reservas, cancelaciones, colas).  
- **Main.cpp** → Contiene el menú principal y la interacción con el usuario.  

---

## 💻 Compilación y ejecución  

### 🔹 Linux / MacOS  
```bash
g++ Main.cpp -o reservas
./sistemaReserva

---

##Autor
Proyecto académico desarrollado por Emmanuel Castaño Sepúlveda
🌐 GitHub
