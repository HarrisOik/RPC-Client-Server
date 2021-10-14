# RPC-Client-Server
Assignment based on the university course Distributed Systems. 
The application is a fully functional commandline, menu based calculator which with the use of RPC technology allows the user to input arrays (and other variables when necessary) to compute specific vector functions (i.e. magnitude, averages, dot product). The application was rated with full mark (10/10)


How to run

After you compile the source code using the provided MakeFile, you begin by opening a terminal and running the RPC server using the following command "*./vect_server*". This terminal will show every function call that is executed by the client (Socket Server).

After succesfully starting the RPC server, you can run this command on a new terminal "*./vect_client*" to see the proper usage for running the Socket server. This terminal will show the connections to the Socket server (the application allows concurent users)

After setting up both the RPC server and the Socket server you are ready to execute the main part of the application (Socket Client) by using the following command in a new terminal "*./client socket_server_address socket_server_port*". Now by choosing an option from the menu, the application will prompt the user to provide the necessary inputs for the calculations.

General Command Usage

/vect_server

/vect_client <rpc_server_address> <port>

/client <socket_server_address> <socket_server_port>
