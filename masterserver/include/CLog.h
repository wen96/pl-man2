///////////////////////////////////////////////////////////////////////////////
/// \file  CLogs.h
/// \brief Archivo de cabecera de una clase especialmente diseñada para
///		   la creación de logs en ficheros de disco
///
/// <b>Fecha Creación:  </b>12 de mayo de 2006           <br>
/// <b>Modificado:      </b>04 de diciembre de 2012      <br>
/// <b>Autor:           </b>Francisco José Gallego Durán.<br>
///////////////////////////////////////////////////////////////////////////////
#pragma once

// INCLUDES
#include <string>
#include <iostream>

// MACROS
#define CLOG CLog::get()

/// <b> CLASE: </b> CLog
///
///	Clase diseñada para la creación y el mantenimiento de un Log en disco <br>
/// con posibilidad de visualizarlo simultáneamente en la terminal a voluntad. <br>
/// <b>IMPORTANTE: </b> Definiendo la constante CLOG_NO_LOGGING se pueden <br>
/// desactivar los logs <br>
///
class CLog
{
public:
    static CLog& get() { static CLog p; return p; }

	/// Métodos para manejar el log
    void setLogFile     (std::string ruta);
    void closeLogFile   ();
	void logToConsole	(bool mostrar);
    void logToFile      (bool mostrar);

    /// Métodos para logear
    void    print          (const char* formato, ...) const;
private:
    CLog ();
    ~CLog();

    bool            m_bMostrarPorConsola;
    bool            m_bMostrarEnArchivo;
    std::ofstream   *m_ostreamFile;
};
