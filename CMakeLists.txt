add_executable(
        archiver
        archiver.cpp
        constatns.h reader.cpp reader.h writer.cpp writer.h encoder.cpp encoder.h decoder.cpp decoder.h huffman.cpp huffman.h one_file_encoder.cpp one_file_encoder.h one_file_decoder.cpp one_file_decoder.h heap.h cla_parser.cpp cla_parser.h archiver_exceptions.cpp archiver_exceptions.h)

add_catch(test_archiver_my test.cpp constatns.h reader.cpp reader.h writer.cpp writer.h encoder.cpp encoder.h decoder.cpp decoder.h huffman.cpp huffman.h one_file_encoder.cpp one_file_encoder.h one_file_decoder.cpp one_file_decoder.h heap.h cla_parser.cpp cla_parser.h archiver_exceptions.cpp archiver_exceptions.h)