R"MAPA(
<style>
[hidden]{display:none!important}*{box-sizing:border-box}body{margin:0;background:#f5f7f5;color:#203e33;font:15px/1.45 system-ui,-apple-system,Segoe UI,sans-serif}button,input,select{font:inherit}button,summary{cursor:pointer}button,input,select{border:1px solid #d4ded6;border-radius:8px;background:white;color:inherit;padding:9px 12px}button[aria-pressed=true]{background:#185b45;color:white;border-color:#185b45}button:disabled{opacity:.4;cursor:default}button:focus-visible,select:focus-visible,input:focus-visible,summary:focus-visible{outline:3px solid #82ab92;outline-offset:3px}header{max-width:1450px;margin:auto;padding:24px 28px;display:flex;align-items:center;justify-content:space-between;gap:16px}h1{font-size:24px;letter-spacing:-.8px;margin:0}h1 span{color:#62816e;font-weight:400;font-size:15px;letter-spacing:0;margin-left:12px}.session{font-size:12px;color:#65796e}main{max-width:1450px;margin:auto;padding:0 28px;display:grid;grid-template-columns:minmax(0,1fr) 315px;gap:20px}h2{font-size:17px;margin:0}h3{font-size:16px;margin:0 0 10px}p{margin:8px 0}.filters{display:flex;align-items:end;gap:12px;flex-wrap:wrap;padding:16px 18px;background:white;border:1px solid #dce4dd;border-bottom:0;border-radius:12px 12px 0 0}.field{display:grid;gap:5px;min-width:125px}.field.aula{flex:1;min-width:180px}label{font-size:12px;color:#5a7264}select,input{width:100%;min-width:0}.map-shell{border:1px solid #dce4dd;border-radius:0 0 12px 12px;overflow:hidden;background:#eaece5}.map-viewport{overflow:auto;max-height:72vh;overscroll-behavior:contain}.map-canvas{display:block;width:100%;height:auto;aspect-ratio:1280/470}.map-canvas text{font-family:inherit}.map-canvas [role=button]{cursor:pointer}.map-canvas [role=button]:focus circle{stroke:#12291f;stroke-width:4}.map-canvas .zone{fill:white;stroke:#6e8d76;stroke-width:2}.map-canvas .chosen{fill:#185b45;stroke:white;stroke-width:3}.map-canvas .alert-pin{fill:#ba4436;stroke:white;stroke-width:3}.map-canvas .edge{stroke:#b9ccbe;stroke-width:3}.map-canvas .route{fill:none;stroke:#c96038;stroke-width:7}.zone-label{fill:#47614f;font-size:15px}.reference-hit:hover circle,.reference-hit:focus circle{fill:#185b4555;stroke:white;stroke-width:4}.map-bottom{display:flex;align-items:center;justify-content:space-between;gap:10px;padding:12px 15px;background:white;border-top:1px solid #dce4dd}.map-note{font-size:12px;color:#65796e;max-width:65%}.zoom{display:flex;align-items:center;gap:7px;flex-wrap:wrap}.zoom button{padding:5px 10px}.zoom span{font-size:12px;min-width:36px;text-align:center}.sidebar{min-width:0}.sidebar:has(#detail-panel[hidden]){display:block}.panel{background:white;border:1px solid #dce4dd;border-radius:12px;padding:16px;margin-bottom:14px}.panel-heading{display:flex;justify-content:space-between;align-items:center}.counter{font-size:12px;color:#65796e}.incidents{max-height:420px;overflow:auto}.incident{display:block;width:100%;text-align:left;margin-top:9px;padding:12px}.incident strong{display:block;font-size:14px;font-weight:600}.incident .muted{margin-top:3px}.muted,.empty{font-size:12px;color:#65796e}.incident[aria-pressed=true] .muted{color:#d5e6db}.detail{overflow-wrap:anywhere}.detail dl{display:grid;grid-template-columns:74px minmax(0,1fr);gap:7px;font-size:13px;margin:12px 0}.detail dt{color:#65796e}.detail dd{margin:0}.detail p{font-size:13px}.detail .location-summary{font-size:15px;font-weight:600;color:#214b38}.detail .muted{font-size:12px}.more{max-width:1394px;margin:18px auto 28px}.more>summary{display:inline-block;color:#4b6958;font-size:13px;padding:8px 0}.more>summary::before{content:'+ ';font-size:16px}.more[open]>summary::before{content:'− '}.advanced-content{border-top:1px solid #dce4dd;margin-top:8px;padding-top:18px;display:grid;grid-template-columns:repeat(3,minmax(0,1fr));gap:20px}.advanced-content h3{font-size:14px}.advanced-content label{display:block;margin:10px 0 5px}.advanced-content p{font-size:12px;color:#65796e}.advanced-actions{display:flex;gap:8px;flex-wrap:wrap}.advanced-actions button{font-size:12px}.room-grid{display:grid;grid-template-columns:repeat(2,minmax(0,1fr));gap:6px;max-height:270px;overflow:auto;margin-top:8px}.room-item{text-align:left;font-size:12px;padding:9px;overflow-wrap:anywhere}.room-item strong,.room-item small{display:block}.room-item strong{font-size:14px}.room-item small{color:#65796e;margin-top:3px}.room-item[aria-pressed=true] small{color:#d5e6db}.room-count{color:#a73c30!important}.block-selectors{display:flex;gap:5px;flex-wrap:wrap;margin-top:10px}.block-selectors button{font-size:12px;padding:6px 8px}.zone-list{display:grid;grid-template-columns:1fr 1fr;gap:5px;margin-top:10px;max-height:240px;overflow:auto}.zone-list button{text-align:left;font-size:12px}.zone-list b{margin-right:5px}.advanced-footer{grid-column:1/-1;border-top:1px solid #dce4dd;padding-top:10px}.sr{position:absolute;width:1px;height:1px;overflow:hidden;clip-path:inset(50%)}a{color:#386b50}summary{list-style:none}summary::-webkit-details-marker{display:none}@media(max-width:900px){header{padding:18px}main{padding:0 18px;grid-template-columns:1fr}.sidebar{display:grid;grid-template-columns:1fr 1fr;gap:14px}.panel{margin:0}.more{margin:18px}.advanced-content{grid-template-columns:1fr 1fr}.map-canvas{height:auto}}@media(max-width:560px){header{padding:15px}.session{display:none}h1 span{font-size:12px;margin-left:6px}main{padding:0 12px;gap:12px}.filters{gap:8px;padding:12px}.field{min-width:100px;flex:1}.field.aula{min-width:130px}.filters #clear{font-size:12px;padding:9px}.sidebar{display:block}.panel{margin-bottom:12px}.advanced-content{grid-template-columns:1fr}.map-bottom{padding:10px;align-items:flex-start}.map-note{font-size:11px;max-width:48%}.more{margin:12px}.map-viewport{max-height:65vh}}
</style>
<header><h1>Alerta360<span>Campus UPSA</span></h1><span id="sync" class="session">Sesión actual</span></header>
<main><section aria-label="Mapa del campus"><div class="filters"><div class="field"><label for="room-block">Bloque</label><select id="room-block"></select></div><div class="field aula"><label for="room-choice">Aula</label><select id="room-choice"><option value="0">Elegir aula</option></select></div><button id="clear" type="button">Limpiar</button></div><div class="map-shell"><div id="map-viewport" class="map-viewport"><svg id="map" class="map-canvas" role="group" aria-label="Mapa del campus con incidencias"></svg></div><div class="map-bottom"><span class="map-note">Puntos rojos: incidencias.<br>Ubicación aproximada por bloque.</span><div class="zoom" id="zoom-tools"><button id="zoom-out" type="button" aria-label="Alejar">−</button><span id="zoom-value">100%</span><button id="zoom-in" type="button" aria-label="Acercar">+</button><button id="fit" type="button">Ver todo</button></div></div></div></section><aside class="sidebar"><section class="panel"><div class="panel-heading"><h2>Incidencias</h2><span id="count" class="counter"></span></div><div id="incidents" class="incidents"></div></section><section class="panel" id="detail-panel"><div id="detail" class="detail" aria-live="polite"></div></section></aside></main>
<details class="more" id="more"><summary>Más opciones</summary><div class="advanced-content"><section><h3>Vista del mapa</h3><div class="advanced-actions"><button id="campus" type="button">Campus</button><button id="grafo" type="button">Grafo de atención</button><button id="refresh" type="button">Actualizar</button></div><div class="advanced-actions" id="map-layers" style="margin-top:8px"><button id="clean-layer" type="button">Ilustración</button><button id="source-layer" type="button">Plano original</button></div><div id="block-selectors" class="block-selectors"></div><p id="disclaimer"></p><details id="reference-list"><summary id="reference-summary">Referencias del plano</summary><div id="zones" class="zone-list"></div></details></section><section><h3>Catálogo de aulas</h3><p id="room-totals"></p><label for="room-floor">Planta</label><select id="room-floor"></select><label for="room-query">Buscar por número o nombre</label><input id="room-query" placeholder="Ej.: 203"><p id="room-count"></p><div id="room-grid" class="room-grid"></div></section><section><h3>Filtros y lugares</h3><label for="state">Incidencias que se muestran</label><select id="state"><option value="activas">Activas</option><option value="todas">Todas</option><option>RECIBIDA</option><option>PENDIENTE</option><option>ASIGNADA</option><option>RESUELTA</option><option>CANCELADA</option></select><label for="search">Buscar en el campus</label><input id="search" placeholder="Ej.: biblioteca"><label for="locations">Lugar</label><select id="locations"></select><p id="placeId-info"></p></section><div class="advanced-footer"><p>La ilustración es una referencia visual y no un plano interior. El catálogo no certifica el total de aulas de la universidad. <a href="https://postgrado.upsa.edu.bo/contacto" target="_blank" rel="noopener">Fuente del plano</a> · <a href="https://maps.upsa.edu.bo/" target="_blank" rel="noopener">Catálogo oficial</a></p></div></div></details>
<span id="map-title" hidden></span><span id="map-subtitle" hidden></span><span id="total" hidden></span>
<script>
'use strict';
const DATA=JSON.parse(document.getElementById('datos').textContent), S=DATA.sistema, places=DATA.campus;
const $=id=>document.getElementById(id), NS='http://www.w3.org/2000/svg';
const active=i=>!['RESUELTA','CANCELADA'].includes(i.estado);
const pmap=new Map(places.map(p=>[p.id,p]));
const teachingRooms=places.filter(p=>p.docente);const classroomCount=teachingRooms.filter(p=>/\bAula\b/i.test(p.nombre)).length;
const cleanUri=JSON.parse($('imagen-limpia').textContent).uri;
let layer='clean',roomBlock='A',roomFloor='todas',fullMap=false;
const campusBlocks=[{key:'CENTRAL',name:'Bloque Central',x:270,y:374,n:1},{key:'A',name:'Bloque A',x:535,y:302,n:2},{key:'B',name:'Bloque B',x:300,y:228,n:3},{key:'C',name:'Bloque C',x:997,y:304,n:4},{key:'D',name:'Bloque D',x:1057,y:270,n:5},{key:'E',name:'Bloque E',x:1099,y:218,n:6}];
const blockKey=b=>(b||'').trim().toUpperCase().replace(/^BLOQUE\s+/,'');
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
function incidentPhotoPoint(i){const r=byReference.get(i?.referenciaPlano);if(r)return {x:r.x,y:r.y,reference:r.n,approx:false};const mapped=photoPoint(pmap.get(i?.ubicacion));if(mapped)return mapped;const b=campusBlocks.find(b=>b.key===blockKey(i?.bloque));return b?{x:b.x,y:b.y,reference:null,approx:true,label:b.name}:null;}
function incidentPhotoName(i){return byReference.get(i.referenciaPlano)?.name||pmap.get(i.ubicacion)?.nombre||(i.bloque?'Bloque '+i.bloque+' · Aula '+i.aula:'Sin ubicación');}
let zoom=1,scrollX=0,scrollY=0,overMap=false,lastInteraction=Date.now();document.addEventListener('pointerdown',()=>lastInteraction=Date.now());document.addEventListener('keydown',()=>lastInteraction=Date.now());
let mode='campus', selected=0, placeId=0, zone=0;
try {const saved=JSON.parse(localStorage.getItem('alerta360-simple')||'{}');mode=saved.mode==='grafo'?'grafo':'campus';selected=Number(saved.selected)||0;placeId=Number(saved.placeId)||0;zone=Number(saved.zone)||0;$('state').value=saved.state||'activas';layer=saved.layer==='source'?'source':'clean';roomBlock=saved.roomBlock||'A';roomFloor=saved.roomFloor||'todas';fullMap=!!saved.fullMap;zoom=Math.max(1,Math.min(4,Number(saved.zoom)||1));scrollX=Number(saved.scrollX)||0;scrollY=Number(saved.scrollY)||0;$('more').open=!!saved.moreOpen;}catch{}
const save=()=>{try{localStorage.setItem('alerta360-simple',JSON.stringify({moreOpen:$('more').open,mode,selected,placeId,zone,layer,roomBlock,roomFloor,fullMap,state:$('state').value,zoom,scrollX:$('map-viewport').scrollLeft,scrollY:$('map-viewport').scrollTop}));}catch{}};
const node=(name,attrs={},text)=>{const e=document.createElementNS(NS,name);Object.entries(attrs).forEach(([k,v])=>e.setAttribute(k,v));if(text!==undefined)e.textContent=text;return e;};
const add=(name,attrs,text)=>{const e=node(name,attrs,text);$('map').append(e);return e;};
const graph=[[90,280],[280,110],[280,320],[500,130],[650,310],[790,90],[865,320],[1050,160]];
let markerScale=1,placed=[];
function buttonMap(label,x,y,number,fn,chosen=false,kind='zone'){
const ox=x,oy=y,r=(kind==='zone'?18:17)*markerScale,view=$('map').viewBox.baseVal;const constrain=()=>{x=Math.max(view.x+r+4,Math.min(view.x+view.width-r-4,x));y=Math.max(view.y+r+4,Math.min(view.y+view.height-r-4,y));};constrain();
for(let attempt=0;placed.some(p=>Math.hypot(p.x-x,p.y-y)<p.r+r+5*markerScale)&&attempt<120;attempt++){const angle=attempt*2.4,d=(12+attempt*1.2)*markerScale;x=ox+Math.cos(angle)*d;y=oy+Math.sin(angle)*d;constrain();}
placed.push({x,y,r});
if(x!==ox||y!==oy)add('line',{x1:ox,y1:oy,x2:x,y2:y,stroke:'#879d8c','stroke-width':markerScale});
const g=add('g',{role:'button',tabindex:0,'aria-label':label});
g.append(node('title',{},label));g.append(node('circle',{cx:x,cy:y,r,class:chosen?'chosen':kind}));
g.append(node('text',{x,y:y+5*markerScale,'text-anchor':'middle','font-size':(kind==='zone'?14:11)*markerScale,'font-weight':600,fill:chosen||kind!=='zone'?'white':'#174936'},number));
g.addEventListener('click',fn);g.addEventListener('keydown',e=>{if(e.key==='Enter'||e.key===' '){e.preventDefault();fn();}});return g;}
function choosePlace(id){placeId=Number(id);selected=0;zone=0;mode='campus';save();render();focusPoint(photoPoint(pmap.get(placeId)));}
function detail(){
const box=$('detail');box.replaceChildren();const i=S.incidencias.find(i=>i.id===selected),p=pmap.get(placeId);
$('detail-panel').hidden=!i&&!p;const title=document.createElement('h3');title.textContent=i?'Incidencia #'+i.id:p?(p.docente?'Aula seleccionada':'Lugar seleccionado'):'Seleccioná un punto';box.append(title);
if(i){
const place=pmap.get(i.ubicacion);const location=document.createElement('p');location.className='location-summary';location.textContent=i.bloque?'Bloque '+i.bloque+' · Aula '+i.aula:incidentPhotoName(i);box.append(location);
if(place?.planta){const floor=document.createElement('p');floor.className='muted';floor.textContent=place.planta;box.append(floor);}
const dl=document.createElement('dl');[['Gravedad',i.gravedad?i.gravedad+' / 5':'Sin clasificar'],['Estado',i.estado.toLocaleLowerCase('es')]].forEach(([k,v])=>{const dt=document.createElement('dt'),dd=document.createElement('dd');dt.textContent=k;dd.textContent=v;dl.append(dt,dd);});box.append(dl);
if(i.ruta.length){const route=document.createElement('p');route.textContent='Ruta: '+i.ruta.join(' → ')+' · '+i.costo+' min';box.append(route);}
}else if(p){const name=document.createElement('p');name.className='location-summary';name.textContent=p.nombre;box.append(name);const floor=document.createElement('p');floor.className='muted';floor.textContent=[p.bloque,p.planta].filter(Boolean).join(' · ');box.append(floor);}
else{const hint=document.createElement('p');hint.className='muted';hint.textContent='Tocá una incidencia en el mapa o elegí un aula.';box.append(hint);}
}
function renderLocations(){const text=$('search').value.toLocaleLowerCase('es');const select=$('locations');select.replaceChildren();const first=document.createElement('option');first.value='0';first.textContent='Seleccionar lugar…';select.append(first);places.filter(p=>`${p.id} ${p.nombre} ${p.bloque} ${p.planta}`.toLocaleLowerCase('es').includes(text)).forEach(p=>{const o=document.createElement('option');o.value=p.id;o.textContent='#'+p.id+' · '+p.nombre+(p.planta?' · '+p.planta:'')+(p.posicion?'':' (sin posición)');select.append(o);});select.value=String(placeId);}
function selectRoom(p){roomBlock=blockKey(p.bloque);roomFloor=p.planta;placeId=p.id;selected=0;zone=0;mode='campus';save();render();focusPoint(photoPoint(p));}
function renderRooms(){
$('room-totals').textContent=`${classroomCount} con nombre Aula · ${teachingRooms.length} espacios docentes catalogados (incluye laboratorios y talleres).`;
const blocks=campusBlocks.map(b=>b.key);
$('room-block').replaceChildren();blocks.forEach(key=>{const o=document.createElement('option');o.value=key;o.textContent=key==='CENTRAL'?'Central':key;$('room-block').append(o);});
if(!blocks.includes(roomBlock))roomBlock=blocks[0]||'A';$('room-block').value=roomBlock;
const inBlock=teachingRooms.filter(p=>blockKey(p.bloque)===roomBlock);$('room-choice').replaceChildren();const emptyChoice=document.createElement('option');emptyChoice.value='0';emptyChoice.textContent=inBlock.length?'Elegir aula':'Sin aulas catalogadas';$('room-choice').append(emptyChoice);inBlock.forEach(p=>{const option=document.createElement('option');option.value=p.id;const code=p.nombre.match(/^[A-E]-(\d{3})\b/);option.textContent=code?code[1]+' · '+p.planta:p.nombre;$('room-choice').append(option);});$('room-choice').disabled=!inBlock.length;$('room-choice').value=inBlock.some(p=>p.id===placeId)?String(placeId):'0';
const floors=[...new Set(teachingRooms.filter(p=>blockKey(p.bloque)===roomBlock).map(p=>p.planta))].sort();
if(roomFloor!=='todas'&&!floors.includes(roomFloor))roomFloor='todas';$('room-floor').replaceChildren();
['todas',...floors].forEach(f=>{const o=document.createElement('option');o.value=f;o.textContent=f==='todas'?'Todas las plantas':f;$('room-floor').append(o);});$('room-floor').value=roomFloor;
const q=$('room-query').value.toLocaleLowerCase('es');
const visible=teachingRooms.filter(p=>blockKey(p.bloque)===roomBlock&&(roomFloor==='todas'||p.planta===roomFloor)&&p.nombre.toLocaleLowerCase('es').includes(q));
$('room-count').textContent=visible.length+' espacios · Bloque '+roomBlock;$('room-grid').replaceChildren();
visible.forEach(p=>{const b=document.createElement('button');b.type='button';b.className='room-item';b.setAttribute('aria-label',p.nombre+' · '+p.planta);b.setAttribute('aria-pressed',p.id===placeId);const code=p.nombre.match(/^[A-E]-\d{3}\b/);const title=document.createElement('strong');title.textContent=code?code[0]:'CIAP';const desc=document.createElement('small');desc.textContent=(code?p.nombre.slice(code[0].length).trim():p.nombre)+' · '+p.planta;b.append(title,desc);const count=S.incidencias.filter(i=>active(i)&&i.ubicacion===p.id).length;if(count){const status=document.createElement('small');status.className='room-count';status.textContent=count+' incidencia'+(count===1?'':'s');b.append(status);}b.onclick=()=>selectRoom(p);$('room-grid').append(b);});
if(!visible.length){const msg=document.createElement('p');msg.className='empty';msg.textContent='No hay coincidencias en el catálogo.';$('room-grid').append(msg);}
}
function render(){
$('campus').setAttribute('aria-pressed',mode==='campus');$('grafo').setAttribute('aria-pressed',mode==='grafo');$('map').replaceChildren();$('zones').replaceChildren();placed=[];markerScale=Math.max(1,1120/$('map').clientWidth);
const filtered=S.incidencias.filter(i=>$('state').value==='todas'||($('state').value==='activas'?active(i):i.estado===$('state').value));
$('sync').textContent=S.incidencias.length&&S.incidencias.every(i=>i.descripcion.startsWith('DEMO:'))?'Demostración · incidencias de ejemplo':'Datos de tu sesión de consola';$('total').textContent=S.incidencias.filter(active).length+' activas';$('count').textContent='('+filtered.length+')';$('incidents').replaceChildren();
filtered.forEach(i=>{const b=document.createElement('button');b.className='incident';b.setAttribute('aria-pressed',selected===i.id);const title=document.createElement('strong');title.textContent=i.bloque?'Bloque '+i.bloque+' · Aula '+i.aula:'#'+i.id+' · '+incidentPhotoName(i);const sub=document.createElement('div');sub.className='muted';sub.textContent='#'+i.id+' · Gravedad '+(i.gravedad||'—');b.append(title,sub);b.onclick=()=>{selected=i.id;placeId=i.ubicacion;zone=i.referenciaPlano||0;const room=pmap.get(i.ubicacion);if(room?.docente){roomBlock=blockKey(room.bloque);roomFloor=room.planta;}save();render();if(mode==='campus')focusPoint(incidentPhotoPoint(i));};$('incidents').append(b);});
if(!filtered.length){const e=document.createElement('p');e.className='empty';e.textContent='No hay incidencias en este filtro.';$('incidents').append(e);}
const current=S.incidencias.find(i=>i.id===selected);
if(mode==='campus'){
$('map-title').textContent=layer==='clean'?'Campus UPSA · bloques y aulas':'Campus UPSA · plano original';$('map-subtitle').textContent=layer==='clean'?'Ilustración IA basada en el plano oficial · comparar con Plano original':'Imagen oficial de Postgrado UPSA · referencias 1–36';
$('map-layers').hidden=false;$('clean-layer').setAttribute('aria-pressed',layer==='clean');$('source-layer').setAttribute('aria-pressed',layer==='source');
$('zoom-tools').hidden=false;$('reference-summary').textContent='Referencias del plano original (1–36)';
const view=layer==='clean'&&!fullMap?'0 120 1280 470':'0 0 1280 786';$('map').setAttribute('viewBox',view);$('map').style.aspectRatio=layer==='clean'&&!fullMap?'1280 / 470':'1280 / 786';applyZoom();markerScale=Math.max(.65,1280/$('map').clientWidth);
add('image',{id:'campus-photo',href:layer==='clean'?cleanUri:photoUri,x:0,y:0,width:1280,height:786,preserveAspectRatio:'none','aria-label':layer==='clean'?'Ilustración del campus derivada del plano oficial':'Plano original del campus UPSA'});
if(layer==='source')zoneData.forEach(z=>{const g=add('g',{role:'button',tabindex:0,'aria-label':'Referencia '+z.n+': '+z.name,class:'reference-hit'});g.append(node('title',{},z.n+' · '+z.name));g.append(node('circle',{cx:z.x,cy:z.y,r:14,fill:'transparent',stroke:zone===z.n?'#fff':'transparent','stroke-width':4}));const fn=()=>{zone=z.n;placeId=z.place||0;selected=0;save();render();};g.onclick=fn;g.onkeydown=e=>{if(e.key==='Enter'||e.key===' '){e.preventDefault();fn();}};});
else campusBlocks.forEach(b=>{buttonMap(b.n+' · '+b.name,b.x,b.y,b.key==='CENTRAL'?'CT':b.key,()=>{roomBlock=b.key;roomFloor='todas';selected=0;placeId=0;save();render();focusPoint(b);},roomBlock===b.key);});
$('block-selectors').replaceChildren();campusBlocks.forEach(b=>{const btn=document.createElement('button');btn.type='button';btn.textContent=b.n+' · '+b.name;btn.setAttribute('aria-pressed',roomBlock===b.key);btn.onclick=()=>{roomBlock=b.key;roomFloor='todas';selected=0;placeId=0;mode='campus';save();render();focusPoint(b);};$('block-selectors').append(btn);});
filtered.forEach(i=>{const point=incidentPhotoPoint(i);if(!point)return;const {x,y}=point;const same=filtered.filter(j=>{const p=incidentPhotoPoint(j);return p&&p.x===x&&p.y===y;}),idx=same.indexOf(i),offset=(idx-(same.length-1)/2)*38*markerScale;const markerY=y-40*markerScale;add('line',{x1:x,y1:y,x2:x+offset,y2:markerY,stroke:'#b32e20','stroke-width':3*markerScale});buttonMap('Incidencia #'+i.id+' · '+incidentPhotoName(i)+(point.approx?' (aproximada por bloque)':''),x+offset,markerY,i.id,()=>{selected=i.id;placeId=i.ubicacion;zone=i.referenciaPlano||0;const room=pmap.get(i.ubicacion);if(room?.docente){roomBlock=blockKey(room.bloque);roomFloor=room.planta;}save();render();},selected===i.id,'alert-pin');});
const target=current?incidentPhotoPoint(current):(placeId?photoPoint(pmap.get(placeId)):null);
if(target){add('circle',{cx:target.x,cy:target.y,r:23,fill:'none',stroke:'#fbca39','stroke-width':5});add('circle',{cx:target.x,cy:target.y,r:28,fill:'none',stroke:'#174936','stroke-width':2});}
zoneData.forEach(z=>zoneButton(z.n,z.name,()=>{zone=z.n;selected=0;placeId=z.place||0;save();render();focusPoint(z);}));
$('disclaimer').textContent='Elegí bloque y planta para consultar las aulas del catálogo. La ilustración IA es una referencia visual; el plano original conserva la infraestructura publicada. Los marcadores de aulas señalan el bloque, no una distribución interior verificada. Las rutas del grafo no son mediciones del campus.';
}else{
$('map-layers').hidden=true;$('block-selectors').replaceChildren();$('zoom-tools').hidden=true;$('map').style.width='100%';$('map').style.aspectRatio='1150 / 440';$('reference-summary').textContent='Zonas de atención (0–7)';markerScale=Math.max(1,1150/$('map').clientWidth);$('map-title').textContent='Zonas de atención · 0 a 7';$('map-subtitle').textContent='Grafo del proyecto · conexiones en minutos';$('map').setAttribute('viewBox','0 0 1150 440');
S.aristas.forEach(([a,b,c])=>{const [x1,y1]=graph[a],[x2,y2]=graph[b];add('line',{x1,y1,x2,y2,class:'edge'});add('text',{x:(x1+x2)/2,y:(y1+y2)/2-7,'text-anchor':'middle','font-size':12*markerScale,fill:'#546d5d'},c+' min');});
if(current?.ruta.length){const points=current.ruta.map(z=>graph[z].join(',')).join(' ');add('polyline',{points,class:'route'});}
S.zonas.forEach((name,z)=>{const [x,y]=graph[z];buttonMap('Zona '+z+': '+name,x,y,z,()=>{zone=z;selected=0;placeId=0;save();render();},zone===z);if($('map').clientWidth>800)add('text',{x,y:y+46,'text-anchor':'middle',class:'zone-label'},name.length>23?'Centro de salud':name);const list=filtered.filter(i=>i.zona===z);if(list.length)add('text',{x,y:y-36*markerScale,'text-anchor':'middle',fill:'#b83c2e','font-size':12*markerScale},list.length+' incidencia'+(list.length===1?'':'s'));zoneButton(z,name,()=>{zone=z;selected=0;save();render();});});
$('disclaimer').textContent='Distribución esquemática de las ocho zonas de la consigna. La ruta resaltada es la registrada al asignar; puede incluir una vía cerrada posteriormente. Los números del catálogo real son independientes de estas zonas.';
}
const place=pmap.get(placeId);$('placeId-info').textContent=place?[place.nombre,place.bloque,place.planta].filter(Boolean).join(' · '):'205 lugares del catálogo. Elegí uno para ver su posición.';renderLocations();renderRooms();detail();
}
function applyZoom(){const width=$('map-viewport').clientWidth;$('map').style.width=(width*zoom)+'px';$('zoom-value').textContent=Math.round(zoom*100)+'%';$('zoom-out').disabled=zoom<=1;$('zoom-in').disabled=zoom>=4;}
function changeZoom(value){zoom=Math.max(1,Math.min(4,value));save();render();}
function focusPoint(p){if(!p||mode!=='campus')return;const v=$('map-viewport'),view=$('map').viewBox.baseVal,scale=$('map').clientWidth/view.width;v.scrollLeft=(p.x-view.x)*scale-v.clientWidth/2;v.scrollTop=(p.y-view.y)*scale-v.clientHeight/2;save();}
function zoneButton(n,name,fn){const b=document.createElement('button');const number=document.createElement('b');number.textContent=n;b.append(number,document.createTextNode(name));b.onclick=fn;$('zones').append(b);}
$('zoom-in').onclick=()=>changeZoom(zoom+.5);$('zoom-out').onclick=()=>changeZoom(zoom-.5);$('fit').onclick=()=>{fullMap=true;zoom=1;scrollX=scrollY=0;save();render();$('map-viewport').scrollTo(0,0);};$('map-viewport').addEventListener('pointerenter',()=>overMap=true);$('map-viewport').addEventListener('pointerleave',()=>{overMap=false;save();});
$('clean-layer').onclick=()=>{layer='clean';fullMap=false;zoom=1;save();render();};$('source-layer').onclick=()=>{layer='source';fullMap=true;zoom=1;save();render();};$('room-block').onchange=e=>{roomBlock=e.target.value;roomFloor='todas';selected=0;placeId=0;zone=0;$('room-query').value='';save();render();focusPoint(campusBlocks.find(b=>b.key===roomBlock));};$('room-floor').onchange=e=>{roomFloor=e.target.value;save();render();};$('room-query').oninput=renderRooms;
$('room-choice').onchange=e=>{const room=pmap.get(Number(e.target.value));if(room)selectRoom(room);else{placeId=0;selected=0;save();render();}};$('clear').onclick=()=>{selected=0;placeId=0;zone=0;roomFloor='todas';$('room-query').value='';save();render();};$('more').addEventListener('toggle',()=>save());
$('campus').onclick=()=>{mode='campus';save();render();};$('grafo').onclick=()=>{mode='grafo';save();render();};$('refresh').onclick=()=>locationReload();
function locationReload(){save();window.location.reload();}
$('state').onchange=()=>{save();render();};$('search').oninput=renderLocations;$('locations').onchange=e=>choosePlace(e.target.value);
window.addEventListener('resize',()=>render());
render();$('map-viewport').scrollTo(scrollX,scrollY);
// Archivo local autosuficiente. La consola reescribe la instantanea tras cada operacion.
setInterval(()=>{if(document.visibilityState==='visible'&&!overMap&&Date.now()-lastInteraction>8000&&document.activeElement?.tagName!=='INPUT'&&document.activeElement?.tagName!=='SELECT')locationReload();},8000);
</script>
)MAPA"
