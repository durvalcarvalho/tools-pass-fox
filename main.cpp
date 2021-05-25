#include "tools-pass-fox.hpp"


int main(int argc, char ** argv) {
    ToolsPassFox tpf;

    tpf.filepass = "adminadmin";

    if( tpf.export_file( tpf.filepass ) ) {
        std::cout << "Exportado com sucesso!" << std::endl;
    }

    else {
        std::cout << "Falha ao exportar!" << std::endl;
    }

    return 0;
}