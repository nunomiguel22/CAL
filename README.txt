
APIs: GraphViewer

Ficheiros de input (Pasta Data):
clients.txt - Ficheiro com 4 utilizadores com dados prefeitos de maneira a testar os algoritmos
Porto/ - O programa usa o mapa do porto fornecido no moodle 
		mais um ficheiro com nome de ruas para cada vertice feito pelo grupo

Compilação: 

	Linux: simplesmente usar o makefile

	Windows:
Importar projeto para ide ou com g++ usar o seguinte comando na raiz da pasta:
g++ source/main.cpp source/graphviewer/graphviewer.cpp source/graphviewer/connection.cpp source/rideshare.cpp source/menu.cpp source/User.cpp source/osm/OSMCollection.cpp source/osm/OSMServices.cpp  source/osm/OSMNode.cpp source/utils/FileManager.cpp -o rideshare.exe -Wextra -Wall 

Dependo da versao do g++ a flag "-lws2_32" pode ser necessária devido a componentes do graphviewer

Execução: Para nao ser feita a visualizaçao do graphviewer por preferencia ou para sistemas que nao tenham sistema grafico pode ser usado o argumento "-nogv".