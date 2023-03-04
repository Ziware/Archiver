#include "cla_parser.h"
#include "encoder.h"
#include "decoder.h"

int main(int argc, char** argv) {
    try {
        CLAParser parser(argc, argv);
        std::string archive_name;
        std::vector<std::string> files;
        parser.AddArgument("d", "decompress", "archive_name", "decompress \'archive_name\'", false, &archive_name);
        parser.AddArgument("c", "compress", "archive_name", "compress into \'archive_name\'", true, &archive_name);
        parser.AddMultipleArgument("file1 [file2 ...]", "file1 [or more optional] to compress", &files);
        if (parser.Parse()) {
            return 0;
        }
        if (!files.empty()) {
            Encoder encoder(archive_name, files);
            std::cout << "\n"
                      << "Start encoding into " << archive_name << "..."
                      << "\n";
            encoder.Encode();
            std::cout << "Successfully encoded!\n";
        } else {
            Decoder decoder(archive_name);
            std::cout << "\n"
                      << "Start decoding " << archive_name << "..."
                      << "\n";
            decoder.Decode();
            std::cout << "Successfully decoded!\n";
        }
    } catch (ArchiverExceptions::NoFile& arg) {
        std::cout << "Can't open file " << arg.what() << '\n';
        return 111;
    } catch (ArchiverExceptions::NoMulArg& arg) {
        std::cout << "Cant find multiple_argument which is required\n" << arg.what() << '\n';
        return 111;
    } catch (ArchiverExceptions::OutOfFile& arg) {
        std::cout << "Tried to get EOF\n" << arg.what() << '\n';
        return 111;
    } catch (std::exception& arg) {
        std::cout << "Unknown exception\n" << arg.what() << '\n';
        return 111;
    }

    return 0;
}