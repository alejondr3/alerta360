R"MAPA(
<style>
*{box-sizing:border-box}body{margin:0;color:#17302c;background:#f3f6f4;font:15px/1.5 system-ui,-apple-system,Segoe UI,sans-serif}button,input,select{font:inherit}button,a{touch-action:manipulation}button{cursor:pointer}header{padding:22px 30px;background:#123e33;color:white;display:flex;justify-content:space-between;align-items:center;gap:20px}header small{color:#b4d8cb;letter-spacing:.15em}h1{font-size:24px;margin:2px 0}header a{color:#d2eee1}main{max-width:1550px;margin:auto;padding:24px;display:grid;grid-template-columns:minmax(0,1fr) 340px;gap:22px}.toolbar{display:flex;flex-wrap:wrap;align-items:center;gap:10px;margin-bottom:14px}button{border:1px solid #cbd8d1;border-radius:9px;padding:9px 13px;color:#234b3d;background:white}button[aria-pressed=true]{background:#165c46;color:white;border-color:#165c46}input,select{padding:10px;border:1px solid #cbd8d1;border-radius:8px;min-width:0;background:white}input{width:100%}select{max-width:100%}.map-shell{position:relative;background:#e8f0e9;border:1px solid #cbd8d1;border-radius:16px;overflow:hidden}.map-heading{padding:18px 20px 0;display:flex;align-items:flex-start;justify-content:space-between;gap:12px}h2{font-size:18px;margin:0}p{margin:5px 0 14px}.muted{color:#60756b;font-size:13px}.map-canvas{display:block;width:100%;height:auto;aspect-ratio:1280/786;background:#dddcd2}.map-viewport{overflow:auto;max-height:76vh;overscroll-behavior:contain}.map-tools{display:flex;flex-wrap:wrap;align-items:center;gap:8px;padding:10px 18px}.map-tools button{padding:6px 12px}.reference-hit{cursor:pointer}.reference-hit:hover circle,.reference-hit:focus circle{stroke:#fff;fill:#164e3b80;stroke-width:4}.photo-note{font-size:12px;padding:0 18px 10px;color:#526e5b}details.references{margin-top:14px}details.references summary{cursor:pointer;font-weight:600;padding:10px 0}.map-canvas text{font-family:inherit}.map-canvas [role=button]{cursor:pointer;outline:none}.map-canvas [role=button]:focus circle{stroke:#111;stroke-width:4}.map-canvas .zone{fill:#fff;stroke:#5f8975;stroke-width:2}.map-canvas .chosen{fill:#1a654d;stroke:#0d3d2e}.map-canvas .chosen-text{fill:#fff}.map-canvas .edge{stroke:#b2c8b9;stroke-width:3}.map-canvas .route{stroke:#cc5b31;stroke-width:7;fill:none}.map-canvas .alert-pin{fill:#c54536;stroke:white;stroke-width:3}.map-canvas .selected-pin{fill:#b34c26;stroke:white;stroke-width:3}.zone-label{fill:#415a4d;font-size:15px}.legend{padding:14px 20px;display:flex;gap:18px;flex-wrap:wrap;border-top:1px solid #cbd8d1;font-size:13px}.dot{display:inline-block;width:10px;height:10px;border-radius:50%;margin-right:5px}.zone-list{display:grid;grid-template-columns:repeat(2,minmax(0,1fr));gap:7px;margin-top:16px}.zone-list button{text-align:left;font-size:13px}.zone-list b{display:inline-flex;width:25px;height:25px;align-items:center;justify-content:center;border-radius:50%;background:#e3eee6;margin-right:6px;color:#174936}aside{min-width:0}.panel{background:white;border:1px solid #d8e1da;border-radius:13px;padding:18px;margin-bottom:15px}.panel label{display:block;font-size:13px;margin:10px 0 5px}.incidents{max-height:340px;overflow:auto}.incident{display:block;width:100%;text-align:left;margin-top:9px;border-radius:9px}.incident strong{font-size:15px}.tag{display:inline-block;font-size:11px;letter-spacing:.02em;color:#9e392c;background:#fff1eb;padding:3px 6px;border-radius:5px}.empty{padding:18px 0;color:#60756b}.detail{overflow-wrap:anywhere}.detail h3{margin:0 0 10px}.detail dl{display:grid;grid-template-columns:100px 1fr;font-size:13px;gap:8px;margin:14px 0}.detail dt{color:#60756b}.detail dd{margin:0}.note{font-size:12px;color:#60756b;margin:14px 2px}.action{background:#eaf2ec;padding:10px;border-radius:8px;color:#335a48;font-size:13px}footer{padding:0 26px 22px;color:#60756b;font-size:12px}.sr{position:absolute;width:1px;height:1px;overflow:hidden;clip-path:inset(50%)}@media(max-width:1000px){main{grid-template-columns:1fr}.map-canvas{height:auto}aside{display:grid;grid-template-columns:1fr 1fr;gap:15px}.panel{margin:0}.detail-panel{grid-column:1/-1}}@media(max-width:600px){header{padding:15px;align-items:flex-start}header a{font-size:12px}main{padding:12px;gap:14px}aside{display:block}.panel{margin-bottom:12px}.map-canvas{height:auto}.map-heading{padding:14px 12px 0}.legend{padding:12px}.zone-list{grid-template-columns:1fr 1fr}.zone-list button{font-size:12px;padding:8px}h1{font-size:21px}}
</style>
<header><div><small>UPSA · CENTRO DE SOPORTE</small><h1>Alerta360 <span style="font-weight:400;opacity:.6">/ mapa</span></h1></div><a href="https://maps.upsa.edu.bo/" target="_blank" rel="noopener">Abrir mapa oficial ↗</a></header>
<main><section aria-label="Mapa de incidencias"><div class="toolbar"><button id="campus" type="button">Campus UPSA</button><button id="grafo" type="button">Zonas de atención 0–7</button><button id="refresh" type="button">Actualizar</button><span class="muted" id="sync">Datos de tu sesión de consola</span></div><div class="map-shell"><div class="map-heading"><div><h2 id="map-title">Zonas del campus</h2><p id="map-subtitle" class="muted"></p></div><span class="tag" id="total"></span></div><div class="map-tools" id="zoom-tools"><button id="zoom-out" type="button" aria-label="Alejar plano">−</button><span id="zoom-value">100%</span><button id="zoom-in" type="button" aria-label="Acercar plano">+</button><button id="fit" type="button">Ver completo</button><span class="muted">Ampliá y desplazá el plano para leer sus números.</span></div><div id="map-viewport" class="map-viewport"><svg id="map" class="map-canvas" role="group" aria-label="Campus con zonas numeradas y ubicaciones de incidencias"></svg></div><div class="legend"><span><i class="dot" style="background:#165c46"></i>Zona seleccionada</span><span><i class="dot" style="background:#c54536"></i>Incidencia activa</span><span><i class="dot" style="background:#cc5b31"></i>Ruta registrada en el grafo</span></div></div><details class="references" id="reference-list"><summary id="reference-summary">Referencias numeradas del plano (1–36)</summary><div class="zone-list" id="zones" aria-label="Zonas numeradas"></div></details><p class="note" id="disclaimer"></p></section><aside><section class="panel"><h2>Buscar un lugar</h2><label for="search">Nombre, bloque o número del lugar</label><input id="search" placeholder="Ej.: biblioteca, bloque D, 173"><label for="locations">Ubicaciones del catálogo oficial</label><select id="locations" style="width:100%" aria-label="Elegir ubicación"></select><p class="note" id="placeId-info"></p></section><section class="panel"><h2>Incidencias <span id="count"></span></h2><label for="state">Mostrar</label><select id="state" style="width:100%"><option value="activas">Activas</option><option value="todas">Todas</option><option>RECIBIDA</option><option>PENDIENTE</option><option>ASIGNADA</option><option>RESUELTA</option><option>CANCELADA</option></select><div id="incidents" class="incidents"></div></section><section class="panel detail-panel"><div id="detail" class="detail" aria-live="polite"></div></section></aside></main><footer>Imagen original: <a href="https://postgrado.upsa.edu.bo/contacto" target="_blank" rel="noopener">Campus UPSA · Postgrado</a>. Se conservan sus referencias 1–36 y sus leyendas. Los ID del catálogo #1–#205 y las zonas de atención 0–7 son independientes.</footer>
<script>
'use strict';
const DATA=JSON.parse(document.getElementById('datos').textContent), S=DATA.sistema, places=DATA.campus;
const $=id=>document.getElementById(id), NS='http://www.w3.org/2000/svg';
const active=i=>!['RESUELTA','CANCELADA'].includes(i.estado);
const pmap=new Map(places.map(p=>[p.id,p]));
const zoneData=[
{n:1,name:'Parqueo Administrativo',x:136,y:263,place:186},
{n:2,name:'DIP · Dirección de Postgrado',x:207,y:255},
{n:3,name:'Salón Auditorio',x:231,y:348,place:10},
{n:4,name:'CIAP · Asesoramiento Psicológico',x:250,y:236,place:153},
{n:5,name:'Facultad de Arquitectura, Diseño y Urbanismo',x:271,y:237,place:152},
{n:6,name:'CENACE · Educación Continua',x:273,y:267,place:42},
{n:7,name:'Facultades del Edificio Central',x:275,y:337},
{n:8,name:'Ventanilla Única',x:297,y:278,place:29},
{n:9,name:'Patio Central',x:328,y:315,place:203},
{n:10,name:'Trámites y Títulos',x:298,y:392,place:88},
{n:11,name:'Ingreso Peatonal',x:311,y:448,place:185},
{n:12,name:'Parqueo Edificio Central',x:382,y:169,place:188},
{n:13,name:'Cabaña Jatata',x:375,y:246,place:12},
{n:14,name:'Escalera Central',x:393,y:309,place:205},
{n:15,name:'Internacionalización',x:409,y:292,place:93},
{n:16,name:'Admisiones y Registro / Contabilidad',x:364,y:359,place:3},
{n:17,name:'Pórtico',x:401,y:358,place:201},
{n:18,name:'Alumni / Asuntos Estudiantiles / Admisiones',x:427,y:345,place:94},
{n:19,name:'Rampa',x:465,y:270},
{n:20,name:'Cabañas Modulares',x:506,y:199,place:13},
{n:21,name:'DABE · Bienestar Estudiantil',x:586,y:205,place:92},
{n:22,name:'Extensión Cultural / IncubaUPSA',x:494,y:371,place:16},
{n:23,name:'Parqueo Docente',x:518,y:440,place:187},
{n:24,name:'Parqueo Externo',x:369,y:609,place:190},
{n:25,name:'Parqueo Edificio Central',x:659,y:236,place:189},
{n:26,name:'Biblioteca (P4)',x:644,y:298,place:173},
{n:27,name:'Aula Magna',x:632,y:366,place:23},
{n:28,name:'Parqueo CC UPSA',x:754,y:430},
{n:29,name:'Centro de Convenciones',x:814,y:340,place:46},
{n:30,name:'Plaza de Banderas',x:830,y:410,place:48},
{n:31,name:'Polideportivo',x:920,y:298,place:49},
{n:32,name:'Coordinación de Deportes',x:956,y:286,place:50},
{n:33,name:'Parqueo Polideportivo',x:1074,y:399,place:191},
{n:34,name:'Parqueo Ingeniería',x:1064,y:164,place:192},
{n:35,name:'Facultad de Ingeniería (P2)',x:1081,y:319,place:133},
{n:36,name:'Laboratorios de Ingeniería',x:1135,y:299}
];
const photoUri=JSON.parse($('imagen-campus').textContent).uri;
const byReference=new Map(zoneData.map(z=>[z.n,z]));
const exactReferences={3:16,10:3,12:13,13:20,16:22,23:27,24:27,27:0,29:8,42:6,46:29,47:29,48:30,49:31,50:32,83:16,88:10,89:7,90:7,91:7,92:21,93:15,94:18,100:18,110:22,152:5,153:4,133:35,173:26,185:11,186:1,187:23,188:12,189:25,190:24,191:33,192:34,201:17,203:9,205:14};
const blockAnchors={'Bloque Central':[270,374],'Bloque A':[535,302],'Bloque B':[300,228],'Bloque C':[997,304],'Bloque D':[1057,270],'Bloque E':[1099,218]};
function photoPoint(p){
if(!p?.posicion)return null;
if(p.id===27)return {x:324,y:292,reference:null,approx:false};
if(p.id===51)return {x:835,y:236,reference:null,approx:true,label:'Cancha de fútbol'};
const ref=byReference.get(exactReferences[p.id]);
if(ref)return {x:ref.x,y:ref.y,reference:ref.n,approx:false};
const anchor=blockAnchors[p.bloque];
return anchor?{x:anchor[0],y:anchor[1],reference:null,approx:true,label:p.bloque}:null;
}
function incidentPhotoPoint(i){const r=byReference.get(i?.referenciaPlano);return r?{x:r.x,y:r.y,reference:r.n,approx:false}:photoPoint(pmap.get(i?.ubicacion));}
function incidentPhotoName(i){return byReference.get(i.referenciaPlano)?.name||pmap.get(i.ubicacion)?.nombre||'Sin ubicación';}
let zoom=1,scrollX=0,scrollY=0,overMap=false,lastInteraction=Date.now();document.addEventListener('pointerdown',()=>lastInteraction=Date.now());document.addEventListener('keydown',()=>lastInteraction=Date.now());
let mode='campus', selected=0, placeId=0, zone=0;
try {const saved=JSON.parse(localStorage.getItem('alerta360-map')||'{}');mode=saved.mode==='grafo'?'grafo':'campus';selected=Number(saved.selected)||0;placeId=Number(saved.placeId)||0;zone=Number(saved.zone)||0;$('state').value=saved.state||'activas';zoom=Math.max(1,Math.min(4,Number(saved.zoom)||1));scrollX=Number(saved.scrollX)||0;scrollY=Number(saved.scrollY)||0;}catch{}
const save=()=>{try{localStorage.setItem('alerta360-map',JSON.stringify({mode,selected,placeId,zone,state:$('state').value,zoom,scrollX:$('map-viewport').scrollLeft,scrollY:$('map-viewport').scrollTop}));}catch{}};
const node=(name,attrs={},text)=>{const e=document.createElementNS(NS,name);Object.entries(attrs).forEach(([k,v])=>e.setAttribute(k,v));if(text!==undefined)e.textContent=text;return e;};
const add=(name,attrs,text)=>{const e=node(name,attrs,text);$('map').append(e);return e;};
const graph=[[90,280],[280,110],[280,320],[500,130],[650,310],[790,90],[865,320],[1050,160]];
let markerScale=1,placed=[];
function buttonMap(label,x,y,number,fn,chosen=false,kind='zone'){
const ox=x,oy=y,r=(kind==='zone'?18:17)*markerScale;
for(let attempt=0;placed.some(p=>Math.hypot(p.x-x,p.y-y)<p.r+r+5*markerScale)&&attempt<120;attempt++){const angle=attempt*2.4,d=(12+attempt*1.2)*markerScale;x=ox+Math.cos(angle)*d;y=oy+Math.sin(angle)*d;}
placed.push({x,y,r});
if(x!==ox||y!==oy)add('line',{x1:ox,y1:oy,x2:x,y2:y,stroke:'#879d8c','stroke-width':markerScale});
const g=add('g',{role:'button',tabindex:0,'aria-label':label});
g.append(node('title',{},label));g.append(node('circle',{cx:x,cy:y,r,class:chosen?'chosen':kind}));
g.append(node('text',{x,y:y+5*markerScale,'text-anchor':'middle','font-size':(kind==='zone'?14:11)*markerScale,'font-weight':600,fill:chosen||kind!=='zone'?'white':'#174936'},number));
g.addEventListener('click',fn);g.addEventListener('keydown',e=>{if(e.key==='Enter'||e.key===' '){e.preventDefault();fn();}});return g;}
function choosePlace(id){placeId=Number(id);selected=0;zone=0;mode='campus';save();render();focusPoint(photoPoint(pmap.get(placeId)));}
function detail(){
const box=$('detail');box.replaceChildren();const i=S.incidencias.find(i=>i.id===selected), p=pmap.get(placeId);
const reference=mode==='campus'?byReference.get(zone):null;const title=document.createElement('h3');title.textContent=i?'Incidencia #'+i.id:reference?'Referencia '+reference.n:p?'Lugar #'+p.id:'Ubicá el problema';box.append(title);if(reference){const name=document.createElement('p');name.textContent=reference.name;box.append(name);}
if(i){const desc=document.createElement('p');desc.textContent=i.descripcion;box.append(desc);const dl=document.createElement('dl');
[['Estado',i.estado],['Gravedad',i.gravedad||'Sin clasificar'],['Bloque',i.bloque||'Sin especificar'],['Aula',i.aula||'Sin especificar'],['Zona de atención',i.zona<0?'Pendiente de configurar con el nuevo mapa':i.zona+' · '+S.zonas[i.zona]],['Referencia de la foto',i.referenciaPlano?i.referenciaPlano+' · '+byReference.get(i.referenciaPlano)?.name:'Sin referencia directa'],['Lugar UPSA',i.ubicacion&&pmap.has(i.ubicacion)?'#'+i.ubicacion+' · '+pmap.get(i.ubicacion).nombre:'Sin ubicación exacta'],['Ruta',i.ruta.length?i.ruta.join(' → ')+' · '+i.costo+' min (registrados)':'Aún no asignada']].forEach(([k,v])=>{const dt=document.createElement('dt'),dd=document.createElement('dd');dt.textContent=k;dd.textContent=v;dl.append(dt,dd);});box.append(dl);
if(mode==='campus'&&(i.ubicacion||i.referenciaPlano)){const point=incidentPhotoPoint(i);const note=document.createElement('p');note.className='action';note.textContent=point?(point.approx?'Marcador aproximado por bloque/área; no indica un aula exacta.':'Marcador sobre '+(point.reference?'la referencia '+point.reference+' del plano.':'el símbolo del plano.')):'Este lugar no tiene un punto verificado en esta imagen; no se dibuja una posición inventada.';box.append(note);}if(!i.ubicacion&&!i.referenciaPlano){const p=document.createElement('p');p.className='action';p.textContent='Consola: opción 13 → ID '+i.id+' → número de la foto (1–36).';box.append(p);}}
else if(p){const text=document.createElement('p');text.textContent=[p.nombre,p.bloque,p.planta].filter(Boolean).join(' · ');box.append(text);const hint=document.createElement('p');hint.className='action';const point=photoPoint(p);hint.textContent=point?('Consola: opción 12 → ID de incidencia → lugar '+p.id+'. '+(point.approx?'El marcador indica el bloque/área de forma aproximada.':'Coincide con una referencia del plano.')):'Este lugar no tiene un punto verificado en la foto. No se muestra un marcador.';box.append(hint);}
else{const p=document.createElement('p');p.textContent='Seleccioná una zona numerada, un lugar del catálogo o una incidencia para ver el detalle.';box.append(p);}
}
function renderLocations(){const text=$('search').value.toLocaleLowerCase('es');const select=$('locations');select.replaceChildren();const first=document.createElement('option');first.value='0';first.textContent='Seleccionar lugar…';select.append(first);places.filter(p=>`${p.id} ${p.nombre} ${p.bloque} ${p.planta}`.toLocaleLowerCase('es').includes(text)).forEach(p=>{const o=document.createElement('option');o.value=p.id;o.textContent='#'+p.id+' · '+p.nombre+(p.planta?' · '+p.planta:'')+(p.posicion?'':' (sin posición)');select.append(o);});select.value=String(placeId);}
function render(){
$('campus').setAttribute('aria-pressed',mode==='campus');$('grafo').setAttribute('aria-pressed',mode==='grafo');$('map').replaceChildren();$('zones').replaceChildren();placed=[];markerScale=Math.max(1,1120/$('map').clientWidth);
const filtered=S.incidencias.filter(i=>$('state').value==='todas'||($('state').value==='activas'?active(i):i.estado===$('state').value));
$('sync').textContent=S.incidencias.length&&S.incidencias.every(i=>i.descripcion.startsWith('DEMO:'))?'Demostración · incidencias de ejemplo':'Datos de tu sesión de consola';$('total').textContent=S.incidencias.filter(active).length+' activas';$('count').textContent='('+filtered.length+')';$('incidents').replaceChildren();
filtered.forEach(i=>{const b=document.createElement('button');b.className='incident';b.setAttribute('aria-pressed',selected===i.id);const title=document.createElement('strong');title.textContent='#'+i.id+(i.bloque?' · Bloque '+i.bloque+' · Aula '+i.aula:' · Zona '+i.zona);const sub=document.createElement('div');sub.className='muted';sub.textContent=i.estado+' · gravedad '+(i.gravedad||'—')+(i.referenciaPlano?' · foto '+i.referenciaPlano:(i.ubicacion?' · lugar #'+i.ubicacion:''));b.append(title,sub);b.onclick=()=>{selected=i.id;placeId=i.ubicacion;zone=i.referenciaPlano||0;save();render();if(mode==='campus')focusPoint(incidentPhotoPoint(i));};$('incidents').append(b);});
if(!filtered.length){const e=document.createElement('p');e.className='empty';e.textContent='No hay incidencias en este filtro.';$('incidents').append(e);}
const current=S.incidencias.find(i=>i.id===selected);
if(mode==='campus'){
$('map-title').textContent='Campus UPSA · plano completo';$('map-subtitle').textContent='Imagen oficial de Postgrado UPSA · referencias 1–36';
$('zoom-tools').hidden=false;$('reference-summary').textContent='Referencias numeradas del plano (1–36)';$('map').setAttribute('viewBox','0 0 1280 786');$('map').style.aspectRatio='1280 / 786';applyZoom();markerScale=Math.max(.65,1280/$('map').clientWidth);
add('image',{id:'campus-photo',href:photoUri,x:0,y:0,width:1280,height:786,preserveAspectRatio:'xMidYMid meet','aria-label':'Plano completo del campus UPSA con las 36 referencias oficiales y sus leyendas'});
zoneData.forEach(z=>{const g=add('g',{role:'button',tabindex:0,'aria-label':'Referencia '+z.n+': '+z.name,class:'reference-hit'});g.append(node('title',{},z.n+' · '+z.name));g.append(node('circle',{cx:z.x,cy:z.y,r:14,fill:'transparent',stroke:zone===z.n?'#fff':'transparent','stroke-width':4}));const fn=()=>{zone=z.n;placeId=z.place||0;selected=0;save();render();};g.onclick=fn;g.onkeydown=e=>{if(e.key==='Enter'||e.key===' '){e.preventDefault();fn();}};});
filtered.forEach(i=>{const point=incidentPhotoPoint(i);if(!point)return;const {x,y}=point;const same=filtered.filter(j=>{const p=incidentPhotoPoint(j);return p&&p.x===x&&p.y===y;}),idx=same.indexOf(i),offset=(idx-(same.length-1)/2)*38*markerScale;const markerY=y-40*markerScale;add('line',{x1:x,y1:y,x2:x+offset,y2:markerY,stroke:'#b32e20','stroke-width':3*markerScale});buttonMap('Incidencia #'+i.id+' · '+incidentPhotoName(i)+(point.approx?' (aproximada por bloque)':''),x+offset,markerY,i.id,()=>{selected=i.id;placeId=i.ubicacion;zone=i.referenciaPlano||0;save();render();},selected===i.id,'alert-pin');});
const target=current?incidentPhotoPoint(current):(placeId?photoPoint(pmap.get(placeId)):null);
if(target){add('circle',{cx:target.x,cy:target.y,r:23,fill:'none',stroke:'#fbca39','stroke-width':5});add('circle',{cx:target.x,cy:target.y,r:28,fill:'none',stroke:'#174936','stroke-width':2});}
zoneData.forEach(z=>zoneButton(z.n,z.name,()=>{zone=z.n;selected=0;placeId=z.place||0;save();render();focusPoint(z);}));
$('disclaimer').textContent='Foto original completa, incluidas sus leyendas. Usá + para ampliar y desplazate sobre el plano. Los números 1–36 son los de esta imagen; los lugares #1–#205 pertenecen al catálogo. Las aulas sin referencia propia se marcan de forma aproximada en su bloque; los lugares sin correspondencia verificada no reciben un marcador.';
}else{
$('zoom-tools').hidden=true;$('map').style.width='100%';$('map').style.aspectRatio='1150 / 440';$('reference-summary').textContent='Zonas de atención (0–7)';markerScale=Math.max(1,1150/$('map').clientWidth);$('map-title').textContent='Zonas de atención · 0 a 7';$('map-subtitle').textContent='Grafo del proyecto · conexiones en minutos';$('map').setAttribute('viewBox','0 0 1150 440');
S.aristas.forEach(([a,b,c])=>{const [x1,y1]=graph[a],[x2,y2]=graph[b];add('line',{x1,y1,x2,y2,class:'edge'});add('text',{x:(x1+x2)/2,y:(y1+y2)/2-7,'text-anchor':'middle','font-size':12*markerScale,fill:'#546d5d'},c+' min');});
if(current?.ruta.length){const points=current.ruta.map(z=>graph[z].join(',')).join(' ');add('polyline',{points,class:'route'});}
S.zonas.forEach((name,z)=>{const [x,y]=graph[z];buttonMap('Zona '+z+': '+name,x,y,z,()=>{zone=z;selected=0;placeId=0;save();render();},zone===z);if($('map').clientWidth>800)add('text',{x,y:y+46,'text-anchor':'middle',class:'zone-label'},name.length>23?'Centro de salud':name);const list=filtered.filter(i=>i.zona===z);if(list.length)add('text',{x,y:y-36*markerScale,'text-anchor':'middle',fill:'#b83c2e','font-size':12*markerScale},list.length+' incidencia'+(list.length===1?'':'s'));zoneButton(z,name,()=>{zone=z;selected=0;save();render();});});
$('disclaimer').textContent='Distribución esquemática de las ocho zonas de la consigna. La ruta resaltada es la registrada al asignar; puede incluir una vía cerrada posteriormente. Los números del catálogo real son independientes de estas zonas.';
}
const place=pmap.get(placeId);$('placeId-info').textContent=place?[place.nombre,place.bloque,place.planta].filter(Boolean).join(' · '):'205 lugares del catálogo. Elegí uno para ver su posición.';renderLocations();detail();
}
function applyZoom(){const width=$('map-viewport').clientWidth;$('map').style.width=(width*zoom)+'px';$('zoom-value').textContent=Math.round(zoom*100)+'%';$('zoom-out').disabled=zoom<=1;$('zoom-in').disabled=zoom>=4;}
function changeZoom(value){zoom=Math.max(1,Math.min(4,value));save();render();}
function focusPoint(p){if(!p||mode!=='campus')return;const v=$('map-viewport'),scale=$('map').clientWidth/1280;v.scrollLeft=p.x*scale-v.clientWidth/2;v.scrollTop=p.y*scale-v.clientHeight/2;save();}
function zoneButton(n,name,fn){const b=document.createElement('button');const number=document.createElement('b');number.textContent=n;b.append(number,document.createTextNode(name));b.onclick=fn;$('zones').append(b);}
$('zoom-in').onclick=()=>changeZoom(zoom+.5);$('zoom-out').onclick=()=>changeZoom(zoom-.5);$('fit').onclick=()=>{zoom=1;scrollX=scrollY=0;save();render();$('map-viewport').scrollTo(0,0);};$('map-viewport').addEventListener('pointerenter',()=>overMap=true);$('map-viewport').addEventListener('pointerleave',()=>{overMap=false;save();});
$('campus').onclick=()=>{mode='campus';save();render();};$('grafo').onclick=()=>{mode='grafo';save();render();};$('refresh').onclick=()=>locationReload();
function locationReload(){save();window.location.reload();}
$('state').onchange=()=>{save();render();};$('search').oninput=renderLocations;$('locations').onchange=e=>choosePlace(e.target.value);
window.addEventListener('resize',()=>render());
render();$('map-viewport').scrollTo(scrollX,scrollY);
// Archivo local autosuficiente. La consola reescribe la instantanea tras cada operacion.
setInterval(()=>{if(document.visibilityState==='visible'&&!overMap&&Date.now()-lastInteraction>8000&&document.activeElement?.tagName!=='INPUT'&&document.activeElement?.tagName!=='SELECT')locationReload();},8000);
</script>
)MAPA"
