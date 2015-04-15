#include <iostream>
#include <stdlib.h>
#include <fcntl.h> //fcntl bloqueante
#include <sys/stat.h> //stat permisos
#include <sstream> //stringstream
#include <sys/resource.h> //setpriority getpriority

#include "fdstream.h"

using namespace std;

void Error(string s){
	cerr << s << endl;
	exit(1);
}

bool getMessages(boost::fdistream* instreamp);

int main (int argc, char * argv[])
{

	int pipes[2];

	bool pipeBloqueante = false;

	//Comprobacion de errores
	if (argc != 2) Error("Pasame un ejecutable");

	//Cogemos el nombre del proceso del que queremos leer
	string botFile = argv[1];

	//Creamos arrays para almacenar los descriptores de los pipes
	int pipe_in[2];
	int pipe_out[2];

	//Creamos un pipe de entrada
	if (pipe(pipe_in)){
		cerr << "PUMMM creando el pipe de entrada";
	}

	//Creamos el pipe de salida
	if (pipe(pipe_out)){
		cerr << "PUMMM creando el pipe de salida";
	}

	if (fork()==0){//el hijo

		// Hacemos el pipe_out la entrada estandar para el hijo
		close(pipe_out[1]);
		dup2(pipe_out[0], STDIN_FILENO);

		// Hacemos el pipe_in la salida estandar
		dup2(pipe_in[1],STDOUT_FILENO);
		close(pipe_in[0]);

		// Make the pipes non-blocking
		if(false)
		{
			int pd_flags;
			if( (pd_flags = fcntl(pipe_out[0], F_GETFL, 0)) == -1 )
				Error("Couldn't get pd_flags for pipe_out in file ");
			pd_flags |= O_NONBLOCK;
			if( fcntl(pipe_out[0], F_SETFL, pd_flags) == -1 )
				Error("Couldn't change pd_flags for pipe_out in file ");
			if( (pd_flags = fcntl(pipe_in[1], F_GETFL, 0)) == -1 )
				Error("Couldn't get pd_flags for pipe_in in file ");
			pd_flags |= O_NONBLOCK;
			if( fcntl(pipe_in[1], F_SETFL, pd_flags) == -1 )
				Error("Couldn't change pd_flags for pipe_in in file ");
		}

		// Check file attributes
		struct stat filestat;
		if( 0 != stat( botFile.c_str(), &filestat ) )
			Error("Couldn't get stats for file ");
		if( !S_ISREG( filestat.st_mode) )
			Error("Client file isn't regular, error for file ");
		if( !(filestat.st_mode & S_IXOTH) )
			Error("Client file isn't executable for user, error for file ");
		if( (filestat.st_mode & S_ISUID) )
			Error("Set user ID is not allowed, error for file ");

		// Lower priority by one
		int old;
		if( (old = getpriority (PRIO_PROCESS, 0)) == -1 )
			Error("Couldn't get priority for robot ");
		if( setpriority (PRIO_PROCESS, 0, old + 1) == -1)
			Error("Couldn't set priority for robot ");


		if( execl(botFile.c_str(), botFile.c_str(), NULL) == -1 )
			// we are in another process so exiting does not solve the problem
			Error("Couldn't open file ");

		Error("Executable didn't execute, SHOULD NEVER HAPPEN!, error for file");


	}else{//el padre
		close(pipe_out[0]);     // Close input side of pipe_out
		close(pipe_in[1]);      // Close output side of pipe_in

		pipes[0] = pipe_out[1];
		pipes[1] = pipe_in[0];

		// Make the pipes non-blocking
		if(true)
		{
			int pd_flags;
			if( (pd_flags = fcntl(pipe_in[0], F_GETFL, 0)) == -1 )
				Error("Couldn't get pd_flags for pipe_in in file ");
			pd_flags |= O_NONBLOCK;
			if( fcntl(pipe_in[0], F_SETFL, pd_flags) == -1 )
				Error("Couldn't change pd_flags for pipe_in in file ");
			if( (pd_flags = fcntl(pipe_out[1], F_GETFL, 0)) == -1 )
				Error("Couldn't get pd_flags for pipe_out in file ");
			pd_flags |= O_NONBLOCK;
			if( fcntl(pipe_out[1], F_SETFL, pd_flags) == -1 )
				Error("Couldn't change pd_flags for pipe_out in file ");
		}

		boost::fdostream* outstreamp = new boost::fdostream(pipe_out[1]);
		boost::fdistream* instreamp = new boost::fdistream(pipe_in[0]);



		while (!getMessages(instreamp));
		*outstreamp << "COCAINUM" << endl;
		while (!getMessages(instreamp));

		if( instreamp != NULL ) delete instreamp;
		instreamp = NULL;
		if( outstreamp != NULL ) delete outstreamp;
		outstreamp = NULL;
	}

	if( pipes[0] != -1 )
	{
		close(pipes[0]);
		pipes[0] = -1;
	}
	if( pipes[1] != -1 )
	{
		close(pipes[1]);
		pipes[1] = -1;
	}

	return 0;
}

bool getMessages(boost::fdistream* instreamp){

	char streambuffer[4097];
	char buffer[81];
	char text[161];
	char msg_name[81];
	string bufferstreamstring;
	istringstream bufferstream;

	// input stream is set to good status again
	instreamp->clear();
	instreamp->peek();
	int errorstream = instreamp->good();
	if (!errorstream){
		return false;
	}


	// we read 4k at maximum at a turn to avoid the situation where a robot do not stop sending junk
	// in order to stop other robot messages from beeing processed
	instreamp->read(streambuffer,4096);
	bufferstreamstring.assign(streambuffer,instreamp->gcount());
	bufferstream.clear();
	bufferstream.str(bufferstreamstring);
	bufferstream >> ws;
	// super buffer overflow possibility
	//  while( !(*instreamp >> msg_name).eof() )
	while( bufferstream.peek()!=istringstream::traits_type::eof())
	{

		bufferstream.get(msg_name,80,' ');    
		cerr << "Got message: " << msg_name << endl;

		return true;
	}

	return false;
}
