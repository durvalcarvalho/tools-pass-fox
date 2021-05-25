#include "tools-pass-fox.hpp"

ToolsPassFox::ToolsPassFox() {
    home = getenv("HOME");
    file = { "key4.db" };
    src = get_filename( file );
    tmp = "/tmp/pass-fox-kajshdgf";
    des = tmp + "/" + file;
    passfirefox = home + "/pass-firefox.gpg";
}

void ToolsPassFox::make_dir_files() {
    if( ! fs::exists( tmp ) ) {
        fs::create_directories( tmp );
    }
}


std::string ToolsPassFox::get_filename( std::string filename ) {
    std::string dir = home + "/.mozilla/firefox";
    std::string outputfile = "/tmp/bozogo";
    std::string pathfile = "find " + dir + " -name " + filename + " > " + outputfile;
    std::string line;

    const char* cpathfile = pathfile.c_str();
    int stream_file = system( cpathfile );
    std::ifstream file( outputfile );

    file.is_open();

    while( getline(file, line) ) {
        pathfile = line;
    }

    file.close();

    if( stream_file == 0 ) {
        fs::remove( outputfile );
    }

    return pathfile;
}

bool ToolsPassFox::fake_zlib() {
    std::string com = "tar -zcf " + tmp + ".tar.gz" + " -P " + tmp;
    const char * ccom = com.c_str();

    return system( ccom );
}

bool ToolsPassFox::fake_gpgme( int action, std::string filepass ) {
    if( filepass == "") {
        return false;
    }

    std::string com;
    const char * ccom;

    switch ( action ) {
        case 0: // criptografar
            com = "gpg --yes --batch --passphrase=" + filepass + " -c " + tmp + ".tar.gz";
            ccom = com.c_str();
            return system( ccom );

        case 1: // descriptografar
            return false;
    }

    return false;
}

void ToolsPassFox::save_file() {
    fs::copy_file( tmp + ".tar.gz.gpg", passfirefox, fs::copy_options::overwrite_existing );
    fs::remove_all( tmp );
    fs::remove( tmp + ".tar.gz");
    fs::remove( tmp + ".tar.gz.gpg");

}

bool ToolsPassFox::export_file( std::string password) {
    make_dir_files();

    fs::copy_file( src, des, fs::copy_options::overwrite_existing );

    file = "logins.json";
    src = get_filename( file );
    des = tmp + "/" + file;
    fs::copy_file( src, des, fs::copy_options::overwrite_existing );

    fake_zlib();
    filepass = password;

    fake_gpgme( 0, filepass);
    save_file();

    return fs::exists( passfirefox );
}