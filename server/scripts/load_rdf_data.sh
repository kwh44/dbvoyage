#!/bin/bash

cp ./../../extraction_framework/build/*.nt /usr/share/virtuoso-opensource*/vad
dbuser=dba
pass=dba
graph="'http://voyage.org'"
isql-vt 1111 $dbuser $pass exec="DB.DBA.TTLP_MT (file_to_string_output ('/usr/share/virtuoso-opensource-6.1/vad/abstract_article_en.nt'), '', $graph);\
DB.DBA.TTLP_MT (file_to_string_output ('/usr/share/virtuoso-opensource-6.1/vad/cities_section.nt'), '', $graph);\
DB.DBA.TTLP_MT (file_to_string_output ('/usr/share/virtuoso-opensource-6.1/vad/labels_en.nt'), '', $graph);\
DB.DBA.TTLP_MT (file_to_string_output ('/usr/share/virtuoso-opensource-6.1/vad/regions_section.nt'), '', $graph);\
DB.DBA.TTLP_MT (file_to_string_output ('/usr/share/virtuoso-opensource-6.1/vad/see_section.nt'), '', $graph);\
DB.DBA.TTLP_MT (file_to_string_output ('/usr/share/virtuoso-opensource-6.1/vad/wikivoyage_links_en.nt'), '', $graph);"