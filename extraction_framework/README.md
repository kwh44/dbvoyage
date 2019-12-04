<h3>dbvoyage extraction framework</h3>
<h5>Dependencies:</h5>
<ul>
    <li>pugixml - XML processing library</li>
</ul>
<h6>Install pugixml on Linux machine</h6>
<ul>
    <li><code>wget http://github.com/zeux/pugixml/releases/download/v1.10/pugixml-1.10.tar.gz</code></li>
    <li><code>tar -xzf pugixml-1.10.tar.gz</code></li>
    <li><code>cd pugixml-1.10 && mkdir build && cd build && cmake .. && sudo make install</code></li>
</ul>
<h6>Build && run </h6>
<p> Run <code>./run.sh download</code> bash script.<br/>
<code>download</code> option will download the latest wikivoyage dump and store it in dumps directory.</p>
<p> <code>run.sh</code> will run extraction on the latest wikivoyage dump and store rdf data at build directory</p>