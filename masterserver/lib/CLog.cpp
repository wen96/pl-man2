///////////////////////////////////////////////////////////////////////////////
/// \file	CLog.cpp
/// \brief	Implementación de la clase que se dedica a la creación de Logs
///			de depuración en disco.
///
///  <b>Fecha Creación:</b> 12 de mayo de 2006           <br>
///  <b>Modificado:    </b>04 de diciembre de 2012       <br>
///  <b>Autor:         </b> Francisco José Gallego Durán <br>
///////////////////////////////////////////////////////////////////////////////
#include "CLog.h"
#include <cstdio>
#include <cstdarg>
#include <fstream>
#include <iostream>

///
/// <b>Constructor de un nuevo log de depuración </b>
///
///
/// \param ruta    cadena STL con la ruta relativa donde crear el log, incluyendo el nombre de archivo.
/// \param nomLog  nombre que se le pondrá al log como título nada más abrirlo
///
CLog::CLog ()
    : m_bMostrarPorConsola(true),
      m_bMostrarEnArchivo(false),
      m_ostreamFile(NULL)
{
}

///
/// \brief Cierra todas las operaciones de loggeado
///
CLog::~CLog() {
#ifndef CLOG_NO_LOGGING
    closeLogFile();
#endif
}

///
/// \brief Crea un nuevo fichero de log en la ruta indicada si es posible.
///
/// Abre un nuevo archvio LOG en la ruta especificada. Si la ruta correspondía <br>
/// a un archivo log preexistente, lo sustituye, eliminando todo lo que el anterior tuviera.<br>
/// <br>
///
void
CLog::setLogFile (std::string ruta)
{
#ifndef CLOG_NO_LOGGING
    // Cerrar antiguos ficheros de log que pudiéramos haber abierto
    closeLogFile();

    // Abrimos el log para salida, creando archivo nuevo y
    // sustituyendo antiguos en caso de existir
    m_ostreamFile = new std::ofstream(ruta.c_str(), std::ios::trunc);
    if ( !m_ostreamFile )
        print("ERROR: Log file %s could not be opened for output\n", ruta.c_str());
    else
        m_bMostrarEnArchivo = true;
#endif
}

///
/// \brief Cierra cualquier fichero de log que pudiera haber abierto.
///
void
CLog::closeLogFile(){
#ifndef CLOG_NO_LOGGING
    if (m_ostreamFile) {
        m_ostreamFile->close();
        m_ostreamFile->clear();
        m_ostreamFile = NULL;
    }
#endif
}


///
/// <b>Método para añadir líneas de texto a un Log</b>
///
/// Añade al log una cadena de texto, en el mismo formato que haría un printf. <br>
/// Con este método se pueden añadir líneas de texto a un log de la misma forma<br>
/// que si se utilizase printf.
///
/// \param formato		cadena de formato similar a printf
/// \param ...			lista variable de parámetros
///
void
CLog::print (const char* formato, ...) const
{
#ifndef CLOG_NO_LOGGING
	// Comenzamos a procesar la lista de argumentos variable
	va_list vl;
	char texto[4096];

	va_start(vl, formato);
#    ifndef WIN32
      vsnprintf(texto, sizeof(texto), formato, vl);
#    else
      _vsnprintf_s(texto, sizeof(texto), formato, vl);
#    endif
	va_end(vl);

	// Escribimos en el fichero y/o pantalla, según toque
    if (m_bMostrarEnArchivo)  *m_ostreamFile << texto;
    if (m_bMostrarPorConsola) std::cerr      << texto;
#endif
}

///
/// <b> Método para indicar si se quiere mostrar por consola o no </b>
///
/// Con el parámetro que se le pasa se le indica si se quiere que el log se muestre por la<br>
/// consola conforme se vaya produciendo.
///
/// \param mostrar	true si se quiere activar el mostrado por pantalla, false para desactivar
///
void
CLog::logToConsole (bool mostrar)
{
#ifndef CLOG_NO_LOGGING
	// Activar/Desactivar mostrado por consola
	m_bMostrarPorConsola = mostrar;
#endif
}

///
/// <b> Método para activar/desactivar la escritura del log en disco </b>
///
/// Con el parámetro que se le pasa se le indica si se quiere que el log siga escribiéndose o no<br>
/// en disco a partir de ese momento.
///
/// \param mostrar	true si se quiere activar el mostrado por pantalla, false para desactivar
///
void
CLog::logToFile (bool mostrar)
{
#ifndef CLOG_NO_LOGGING
	// Activar/Desactivar mostrado por consola
	m_bMostrarEnArchivo = mostrar;
#endif
}
