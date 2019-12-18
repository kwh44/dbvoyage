<h2>DBvoyage<h2>
<h4>The software used to extract structured data from Wikivoyage</h4>
![DBvoyage Architecture](https://user-images.githubusercontent.com/35134823/71113037-6ab1a880-21d5-11ea-8691-030f1aaed7d8.png)

<h5>Extraction Framework</h5>
<p>Six extractors are written</p>
<ul>
    <li>See section</li>
    <li>Do section</li>
    <li>Article abstract</li>
    <li>Cities section</li>
    <li>Region section</li>
    <li>Article title</li>
    <li>Wikivoyage article link</li>
</ul>
<p>They process Wikivoyage XML dump in parallel. Next step is transitive closure of<br/>
graph from created triples, with at most 12 inner vertexes in path. The final step<br/>
is serialization of triples in N-Triples format.</p>
<h5>Virtuoso Server</h5>
<p>All triples are loaded to the graph over which SPARQL queries can be executed.</p>
<h5>HTTP Server</h5>
<p>Basic nodejs server providing interface with project information, SPARQL queries<br/>
examples and link to editor for writing SPARQL queries over dbvoyage graph.</p>
<h5>The server is running and available by the following link
<a href="http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/">DBvoyage</a></h5>
<p>View all info DBvoyage has about
<a href="http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/ontology/attraction/Lviv Opera and Ballet National Academic Theatre">
Lviv Opera and Ballet National Academic Theatre</a>
</p>
<p>In order to view all attractions DBvoyage knows are located in Ukraine:<br/>
Go to 
<a href="http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/sparql">
SPARQL editor
</a> and write the following query<br/></p>

select<br/>
&nbsp;&nbsp;?attractions<br/>
where<br/>
{<br/>
&nbsp;&nbsp;<<http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/ontology/article/Ukraine>><br/>
&nbsp;&nbsp;<<http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/ontology/property/hasAttraction>><br/>
&nbsp;&nbsp;?attractions<br/>
}<br/>
<br/>

<footer>Created by Andrii Maistruk, 2019.</footer>