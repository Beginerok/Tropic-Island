var VSHADER_SOURCE =
  'attribute vec3 a_Position;\n' +
  'attribute vec4 a_Color;\n'+
  'attribute vec2 a_TexCoord;\n' +
  'varying vec4 v_Color;\n'+
  'varying vec2 v_TexCoord;\n' +
  'uniform mat4 u_ProjMatrix;\n' +
  'uniform mat4 u_ModelMatrix;\n' +
  'void main() {\n' +
  'gl_Position = u_ProjMatrix * u_ModelMatrix * vec4(a_Position,1.0);\n' +
  'v_Color = a_Color;\n'+
  'v_TexCoord = a_TexCoord;\n' +
  '}\n';
var FSHADER_SOURCE =
  '#ifdef GL_ES\n' +
  'precision mediump float;\n' +
  '#endif\n' +
  'varying vec4 v_Color;\n'+
  'uniform sampler2D u_Sampler;\n' +
  'varying vec2 v_TexCoord;\n' +
  'void main() {\n' +
  'gl_FragColor = texture2D(u_Sampler, v_TexCoord);\n' +
  '}\n';
var ANGLE_STEP = -720.0;
var startRotate = 0;
var texturesVec = [], Drum = [], texturefon_;

var ready1 = false, ready2 = false, ready3 = false, ready4 = false, ready5 = false, ready6 = false, ready7 = false, ready8 = false;
var n = 5;
function main() {
  var min=0;
  var max=6;
  for(var i=0;i<30;i++)
  {
    min = Math.ceil(min);
    max = Math.floor(max);
    Drum.push(Math.floor(Math.random() * (max - min + 1)) + min);
  }
  var canvas = document.getElementById('c');
  var nf = document.getElementById('nearFar');
  var gl = getWebGLContext(canvas);
  if (!gl) {
    console.log('Failed to get the rendering context for WebGL');
    return;
  }
  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    console.log('Failed to intialize shaders.');
    return;
  }
  var nj = initVertexBuffers(gl);
  if (nj < 0) {
    console.log('Failed to set the vertex information');
    return;
  }
  var u_ModelMatrix = gl.getUniformLocation(gl.program, 'u_ModelMatrix');
  if (!u_ModelMatrix) {
    console.log('Failed to get the storage location of u_ModelMatrix');
    return;
  }
  var currentAngle = 0.0;
  var modelMatrix = new Matrix4();
  var u_ProjMatrix = gl.getUniformLocation(gl.program,'u_ProjMatrix');
  var projMatrix = new Matrix4();
  var g_near = -1.0, g_far = 1.0;
  projMatrix.setOrtho(-1, 1, -1, 1, g_near, g_far);
  nf.innerHTML = 'near: ' + g_near + ', far: ' + g_far;
  gl.uniformMatrix4fv(u_ProjMatrix, false, projMatrix.elements);
  nf.innerHTML = 'near: ' + g_near + ', far: ' + g_far;
  if (!initTextures(gl)) {
    console.log('Failed to intialize the texture.');
    return;
	}
	gl.clearColor(0.0, 0.0, 0.0, 1.0);
  var tick = function() {
    currentAngle = animate(currentAngle);
    if (currentAngle>=1820 ) {
      startRotate=!startRotate;
      currentAngle = 0.0;
    }
    draw(gl, currentAngle, modelMatrix, u_ModelMatrix, u_ProjMatrix,projMatrix, nf);
    requestAnimationFrame(tick, canvas);
  };  
  tick();
  canvas.onmousedown = function(ev) { click(ev, gl, canvas); };
  buttonSpin.onclick = function(ev) { click(ev, gl, canvas); };
}
//var g_last = Date.now();
function animate(angle) {
  //var now = Date.now();
  //var elapsed = now - g_last;
  //g_last = now;
  if (startRotate) {
   angle+=20;
}
  return angle;
}
function click(ev, gl, canvas) {
  startRotate = !startRotate;
  setTimeout(function(){
  Drum=[];
  var min=0;
  var max=6;
  for(var i=0;i<30;i++)
  {
    min = Math.ceil(min);
    max = Math.floor(max);
    Drum.push(Math.floor(Math.random() * (max - min + 1)) + min);
  }
  }, 1000);
  }
  
function initVertexBuffers(gl) {
  var sleft = []
  var sright = []
  sleft.push(-0.78);
  sleft.push(-0.48);
  sleft.push(-0.16);
  sleft.push(0.16);
  sleft.push(0.48);
  sright.push(-0.48);
  sright.push(-0.16);
  sright.push(0.16);
  sright.push(0.48);
  sright.push(0.78);
  var jIter = 0, nn = 324;
  var buf=[];
  for (var jj=0;jj<sleft.length;jj++)
  {
    var xleft = sleft[jj];
    var xright = sright[jj];
    for (var i = 0; i < n; i++)
		{
			//front up
			var yTex = 1.0 - parseFloat(i / n);
			var yTex2 = 1.0 - parseFloat((i + 1) /n);

			buf[(0 + i * nn) + jIter * n * nn] = xleft;
			buf[(1 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((90.0 - 60.0 / n * i) * 0.0175);
			buf[(2 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((90.0 - 60.0 / n * i) * 0.0175);
			buf[(3 + i * nn) + jIter * n * nn] = 1.0;
			buf[(4 + i * nn) + jIter * n * nn] = 1.0;
			buf[(5 + i * nn) + jIter * n * nn] = 1.0;
			buf[(6 + i * nn) + jIter * n * nn] = 1.0;
			buf[(7 + i * nn) + jIter * n * nn] = 0.0;
			buf[(8 + i * nn) + jIter * n * nn] = yTex;      
      
			buf[(9 + i * nn) + jIter * n * nn] = xleft;
			buf[(10 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(11 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(12 + i * nn) + jIter * n * nn] = 1.0;
			buf[(13 + i * nn) + jIter * n * nn] = 1.0;
			buf[(14 + i * nn) + jIter * n * nn] = 1.0;
			buf[(15 + i * nn) + jIter * n * nn] = 1.0;
			buf[(16 + i * nn) + jIter * n * nn] = 0.0;
			buf[(17 + i * nn) + jIter * n * nn] = yTex2;

			buf[(18 + i * nn) + jIter * n * nn] = xright;
			buf[(19 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((90.0 - 60.0 / n * i) * 0.0175);
			buf[(20 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((90.0 - 60.0 / n * i) * 0.0175);
			buf[(21 + i * nn) + jIter * n * nn] = 1.0;
			buf[(22 + i * nn) + jIter * n * nn] = 1.0;
			buf[(23 + i * nn) + jIter * n * nn] = 1.0;
			buf[(24 + i * nn) + jIter * n * nn] = 1.0;
			buf[(25 + i * nn) + jIter * n * nn] = 1.0;
			buf[(26 + i * nn) + jIter * n * nn] = yTex;

			buf[(27 + i * nn) + jIter * n * nn] = xright;
			buf[(28 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((90.0 - 60.0 / n * i) * 0.0175);
			buf[(29 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((90.0 - 60.0 / n * i) * 0.0175);
			buf[(30 + i * nn) + jIter * n * nn] = 1.0;
			buf[(31 + i * nn) + jIter * n * nn] = 1.0;
			buf[(32 + i * nn) + jIter * n * nn] = 1.0;
			buf[(33 + i * nn) + jIter * n * nn] = 1.0;
			buf[(34 + i * nn) + jIter * n * nn] = 1.0;
			buf[(35 + i * nn) + jIter * n * nn] = yTex;

			buf[(36 + i * nn) + jIter * n * nn] = xleft;
			buf[(37 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(38 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(39 + i * nn) + jIter * n * nn] = 1.0;
			buf[(40 + i * nn) + jIter * n * nn] = 1.0;
			buf[(41 + i * nn) + jIter * n * nn] = 1.0;
			buf[(42 + i * nn) + jIter * n * nn] = 1.0;
			buf[(43 + i * nn) + jIter * n * nn] = 0.0;
			buf[(44 + i * nn) + jIter * n * nn] = yTex2;

			buf[(45 + i * nn) + jIter * n * nn] = xright;
			buf[(46 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(47 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(48 + i * nn) + jIter * n * nn] = 1.0;
			buf[(49 + i * nn) + jIter * n * nn] = 1.0;
			buf[(50 + i * nn) + jIter * n * nn] = 1.0;
			buf[(51 + i * nn) + jIter * n * nn] = 1.0;
			buf[(52 + i * nn) + jIter * n * nn] = 1.0;
			buf[(53 + i * nn) + jIter * n * nn] = yTex2;
			//front middle
			yTex = 1 - parseFloat(i / n);
			yTex2 = 1 - parseFloat((i + 1) / n);     

			buf[(54 + i * nn) + jIter * n * nn] = xleft;
			buf[(55 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((30.0 - 60.0 / n * i) * 0.0175);
			buf[(56 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((30.0 - 60.0 / n * i) * 0.0175);
			buf[(57 + i * nn) + jIter * n * nn] = 1.0;
			buf[(58 + i * nn) + jIter * n * nn] = 1.0;
			buf[(59 + i * nn) + jIter * n * nn] = 1.0;
			buf[(60 + i * nn) + jIter * n * nn] = 1.0;
			buf[(61 + i * nn) + jIter * n * nn] = 0.0;
			buf[(62 + i * nn) + jIter * n * nn] = yTex;

			buf[(63 + i * nn) + jIter * n * nn] = xleft;
			buf[(64 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(65 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(66 + i * nn) + jIter * n * nn] = 1.0;
			buf[(67 + i * nn) + jIter * n * nn] = 1.0;
			buf[(68 + i * nn) + jIter * n * nn] = 1.0;
			buf[(69 + i * nn) + jIter * n * nn] = 1.0;
			buf[(70 + i * nn) + jIter * n * nn] = 0.0;
			buf[(71 + i * nn) + jIter * n * nn] = yTex2;

			buf[(72 + i * nn) + jIter * n * nn] = xright;
			buf[(73 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((30 - 60.0 / n * i) * 0.0175);
			buf[(74 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((30.0 - 60.0 / n * i) * 0.0175);
			buf[(75 + i * nn) + jIter * n * nn] = 1.0;
			buf[(76 + i * nn) + jIter * n * nn] = 1.0;
			buf[(77 + i * nn) + jIter * n * nn] = 1.0;
			buf[(78 + i * nn) + jIter * n * nn] = 1.0;
			buf[(79 + i * nn) + jIter * n * nn] = 1.0;
			buf[(80 + i * nn) + jIter * n * nn] = yTex;

			buf[(81 + i * nn) + jIter * n * nn] = xright;
			buf[(82 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((30.0 - 60.0 / n * i) * 0.0175);
			buf[(83 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((30.0 - 60.0 / n * i) * 0.0175);
			buf[(84 + i * nn) + jIter * n * nn] = 1.0;
			buf[(85 + i * nn) + jIter * n * nn] = 1.0;
			buf[(86 + i * nn) + jIter * n * nn] = 1.0;
			buf[(87 + i * nn) + jIter * n * nn] = 1.0;
			buf[(88 + i * nn) + jIter * n * nn] = 1.0;
			buf[(89 + i * nn) + jIter * n * nn] = yTex;

			buf[(90 + i * nn) + jIter * n * nn] = xleft;
			buf[(91 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(92 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(93 + i * nn) + jIter * n * nn] = 1.0;
			buf[(94 + i * nn) + jIter * n * nn] = 1.0;
			buf[(95 + i * nn) + jIter * n * nn] = 1.0;
			buf[(96 + i * nn) + jIter * n * nn] = 1.0;
			buf[(97 + i * nn) + jIter * n * nn] = 0.0;
			buf[(98 + i * nn) + jIter * n * nn] = yTex2;

			buf[(99 + i * nn) + jIter * n * nn] = xright;
			buf[(100 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(101 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(102 + i * nn) + jIter * n * nn] = 1.0;
			buf[(103 + i * nn) + jIter * n * nn] = 1.0;
			buf[(104 + i * nn) + jIter * n * nn] = 1.0;
			buf[(105 + i * nn) + jIter * n * nn] = 1.0;
			buf[(106 + i * nn) + jIter * n * nn] = 1.0;
			buf[(107 + i * nn) + jIter * n * nn] = yTex2;
			//front down
			yTex = 1 - parseFloat(i / n);
			yTex2 = 1 - parseFloat((i + 1) / n);

			buf[(108 + i * nn) + jIter * n * nn] = xleft;
			buf[(109 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(110 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(111 + i * nn) + jIter * n * nn] = 1.0;
			buf[(112 + i * nn) + jIter * n * nn] = 1.0;
			buf[(113 + i * nn) + jIter * n * nn] = 1.0;
			buf[(114 + i * nn) + jIter * n * nn] = 1.0;
			buf[(115 + i * nn) + jIter * n * nn] = 0.0;
			buf[(116 + i * nn) + jIter * n * nn] = yTex;

			buf[(117 + i * nn) + jIter * n * nn] = xleft;
			buf[(118 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(119 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(120 + i * nn) + jIter * n * nn] = 1.0;
			buf[(121 + i * nn) + jIter * n * nn] = 1.0;
			buf[(122 + i * nn) + jIter * n * nn] = 1.0;
			buf[(123 + i * nn) + jIter * n * nn] = 1.0;
			buf[(124 + i * nn) + jIter * n * nn] = 0.0;
			buf[(125 + i * nn) + jIter * n * nn] = yTex2;

			buf[(126 + i * nn) + jIter * n * nn] = xright;
			buf[(127 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(128 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(129 + i * nn) + jIter * n * nn] = 1.0;
			buf[(130 + i * nn) + jIter * n * nn] = 1.0;
			buf[(131 + i * nn) + jIter * n * nn] = 1.0;
			buf[(132 + i * nn) + jIter * n * nn] = 1.0;
			buf[(133 + i * nn) + jIter * n * nn] = 1.0;
			buf[(134 + i * nn) + jIter * n * nn] = yTex;

			buf[(135 + i * nn) + jIter * n * nn] = xright;
			buf[(136 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(137 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(138 + i * nn) + jIter * n * nn] = 1.0;
			buf[(139 + i * nn) + jIter * n * nn] = 1.0;
			buf[(140 + i * nn) + jIter * n * nn] = 1.0;
			buf[(141 + i * nn) + jIter * n * nn] = 1.0;
			buf[(142 + i * nn) + jIter * n * nn] = 1.0;
			buf[(143 + i * nn) + jIter * n * nn] = yTex;

			buf[(144 + i * nn) + jIter * n * nn] = xleft;
			buf[(145 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(146 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(147 + i * nn) + jIter * n * nn] = 1.0;
			buf[(148 + i * nn) + jIter * n * nn] = 1.0;
			buf[(149 + i * nn) + jIter * n * nn] = 1.0;
			buf[(150 + i * nn) + jIter * n * nn] = 1.0;
			buf[(151 + i * nn) + jIter * n * nn] = 0.0;
			buf[(152 + i * nn) + jIter * n * nn] = yTex2;

			buf[(153 + i * nn) + jIter * n * nn] = xright;
			buf[(154 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(155 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(156 + i * nn) + jIter * n * nn] = 1.0;
			buf[(157 + i * nn) + jIter * n * nn] = 1.0;
			buf[(158 + i * nn) + jIter * n * nn] = 1.0;
			buf[(159 + i * nn) + jIter * n * nn] = 1.0;
			buf[(160 + i * nn) + jIter * n * nn] = 1.0;
			buf[(161 + i * nn) + jIter * n * nn] = yTex2;
			//backup
			yTex = 1 - parseFloat(i / n);
			yTex2 = 1 - parseFloat((i + 1) / n);

			buf[(162 + i * nn) + jIter * n * nn] = xleft;
			buf[(163 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((150.0 - 60.0 / n * i) * 0.0175);
			buf[(164 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((150.0 - 60.0 / n * i) * 0.0175);
			buf[(165 + i * nn) + jIter * n * nn] = 1.0;
			buf[(166 + i * nn) + jIter * n * nn] = 1.0;
			buf[(167 + i * nn) + jIter * n * nn] = 1.0;
			buf[(168 + i * nn) + jIter * n * nn] = 1.0;
			buf[(169 + i * nn) + jIter * n * nn] = 0.0;
			buf[(170 + i * nn) + jIter * n * nn] = yTex;

			buf[(171 + i * nn) + jIter * n * nn] = xleft;
			buf[(172 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(173 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(174 + i * nn) + jIter * n * nn] = 1.0;
			buf[(175 + i * nn) + jIter * n * nn] = 1.0;
			buf[(176 + i * nn) + jIter * n * nn] = 1.0;
			buf[(177 + i * nn) + jIter * n * nn] = 1.0;
			buf[(178 + i * nn) + jIter * n * nn] = 0.0;
			buf[(179 + i * nn) + jIter * n * nn] = yTex2;

			buf[(180 + i * nn) + jIter * n * nn] = xright;
			buf[(181 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((150.0 - 60.0 / n * i) * 0.0175);
			buf[(182 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((150.0 - 60.0 / n * i) * 0.0175);
			buf[(183 + i * nn) + jIter * n * nn] = 1.0;
			buf[(184 + i * nn) + jIter * n * nn] = 1.0;
			buf[(185 + i * nn) + jIter * n * nn] = 1.0;
			buf[(186 + i * nn) + jIter * n * nn] = 1.0;
			buf[(187 + i * nn) + jIter * n * nn] = 1.0;
			buf[(188 + i * nn) + jIter * n * nn] = yTex;

			buf[(189 + i * nn) + jIter * n * nn] = xright;
			buf[(190 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((150.0 - 60.0 / n * i) * 0.0175);
			buf[(191 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((150.0 - 60.0 / n * i) * 0.0175);
			buf[(192 + i * nn) + jIter * n * nn] = 1.0;
			buf[(193 + i * nn) + jIter * n * nn] = 1.0;
			buf[(194 + i * nn) + jIter * n * nn] = 1.0;
			buf[(195 + i * nn) + jIter * n * nn] = 1.0;
			buf[(196 + i * nn) + jIter * n * nn] = 1.0;
			buf[(197 + i * nn) + jIter * n * nn] = yTex;

			buf[(198 + i * nn) + jIter * n * nn] = xleft;
			buf[(199 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(200 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(201 + i * nn) + jIter * n * nn] = 1.0;
			buf[(202 + i * nn) + jIter * n * nn] = 1.0;
			buf[(203 + i * nn) + jIter * n * nn] = 1.0;
			buf[(204 + i * nn) + jIter * n * nn] = 1.0;
			buf[(205 + i * nn) + jIter * n * nn] = 0.0;
			buf[(206 + i * nn) + jIter * n * nn] = yTex2;

			buf[(207 + i * nn) + jIter * n * nn] = xright;
			buf[(208 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(209 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(210 + i * nn) + jIter * n * nn] = 1.0;
			buf[(211 + i * nn) + jIter * n * nn] = 1.0;
			buf[(212 + i * nn) + jIter * n * nn] = 1.0;
			buf[(213 + i * nn) + jIter * n * nn] = 1.0;
			buf[(214 + i * nn) + jIter * n * nn] = 1.0;
			buf[(215 + i * nn) + jIter * n * nn] = yTex2;
			//backmiddle
			yTex = 1 - parseFloat(i / n);
			yTex2 = 1 - parseFloat((i + 1) / n);

			buf[(216 + i * nn) + jIter * n * nn] = xleft;
			buf[(217 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((210.0 - 60.0 / n * i) * 0.0175);
			buf[(218 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((210.0 - 60.0 / n * i) * 0.0175);
			buf[(219 + i * nn) + jIter * n * nn] = 1.0;
			buf[(220 + i * nn) + jIter * n * nn] = 1.0;
			buf[(221 + i * nn) + jIter * n * nn] = 1.0;
			buf[(222 + i * nn) + jIter * n * nn] = 1.0;
			buf[(223 + i * nn) + jIter * n * nn] = 0.0;
			buf[(224 + i * nn) + jIter * n * nn] = yTex;

			buf[(225 + i * nn) + jIter * n * nn] = xleft;
			buf[(226 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(227 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(228 + i * nn) + jIter * n * nn] = 1.0;
			buf[(229 + i * nn) + jIter * n * nn] = 1.0;
			buf[(230 + i * nn) + jIter * n * nn] = 1.0;
			buf[(231 + i * nn) + jIter * n * nn] = 1.0;
			buf[(232 + i * nn) + jIter * n * nn] = 0.0;
			buf[(233 + i * nn) + jIter * n * nn] = yTex2;

			buf[(234 + i * nn) + jIter * n * nn] = xright;
			buf[(235 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((210.0 - 60.0 / n * i) * 0.0175);
			buf[(236 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((210.0 - 60.0 / n * i) * 0.0175);
			buf[(237 + i * nn) + jIter * n * nn] = 1.0;
			buf[(238 + i * nn) + jIter * n * nn] = 1.0;
			buf[(239 + i * nn) + jIter * n * nn] = 1.0;
			buf[(240 + i * nn) + jIter * n * nn] = 1.0;
			buf[(241 + i * nn) + jIter * n * nn] = 1.0;
			buf[(242 + i * nn) + jIter * n * nn] = yTex;

			buf[(243 + i * nn) + jIter * n * nn] = xright;
			buf[(244 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((210.0 - 60.0 / n * i) * 0.0175);
			buf[(245 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((210.0 - 60.0 / n * i) * 0.0175);
			buf[(246 + i * nn) + jIter * n * nn] = 1.0;
			buf[(247 + i * nn) + jIter * n * nn] = 1.0;
			buf[(248 + i * nn) + jIter * n * nn] = 1.0;
			buf[(249 + i * nn) + jIter * n * nn] = 1.0;
			buf[(250 + i * nn) + jIter * n * nn] = 1.0;
			buf[(251 + i * nn) + jIter * n * nn] = yTex;

			buf[(252 + i * nn) + jIter * n * nn] = xleft;
			buf[(253 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(254 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(255 + i * nn) + jIter * n * nn] = 1.0;
			buf[(256 + i * nn) + jIter * n * nn] = 1.0;
			buf[(257 + i * nn) + jIter * n * nn] = 1.0;
			buf[(258 + i * nn) + jIter * n * nn] = 1.0;
			buf[(259 + i * nn) + jIter * n * nn] = 0.0;
			buf[(260 + i * nn) + jIter * n * nn] = yTex2;

			buf[(261 + i * nn) + jIter * n * nn] = xright;
			buf[(262 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(263 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(264 + i * nn) + jIter * n * nn] = 1.0;
			buf[(265 + i * nn) + jIter * n * nn] = 1.0;
			buf[(266 + i * nn) + jIter * n * nn] = 1.0;
			buf[(267 + i * nn) + jIter * n * nn] = 1.0;
			buf[(268 + i * nn) + jIter * n * nn] = 1.0;
			buf[(269 + i * nn) + jIter * n * nn] = yTex2;
			/*back down*/
			yTex = 1 - parseFloat(i / n);
			yTex2 = 1 - parseFloat((i + 1) / n);

			buf[(270 + i * nn) + jIter * n * nn] = xleft;
			buf[(271 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(272 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(273 + i * nn) + jIter * n * nn] = 1.0;
			buf[(274 + i * nn) + jIter * n * nn] = 1.0;
			buf[(275 + i * nn) + jIter * n * nn] = 1.0;
			buf[(276 + i * nn) + jIter * n * nn] = 1.0;
			buf[(277 + i * nn) + jIter * n * nn] = 0.0;
			buf[(278 + i * nn) + jIter * n * nn] = yTex;

			buf[(279 + i * nn) + jIter * n * nn] = xleft;
			buf[(280 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(281 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(282 + i * nn) + jIter * n * nn] = 1.0;
			buf[(283 + i * nn) + jIter * n * nn] = 1.0;
			buf[(284 + i * nn) + jIter * n * nn] = 1.0;
			buf[(285 + i * nn) + jIter * n * nn] = 1.0;
			buf[(286 + i * nn) + jIter * n * nn] = 0.0;
			buf[(287 + i * nn) + jIter * n * nn] = yTex2;

			buf[(288 + i * nn) + jIter * n * nn] = xright;
			buf[(289 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(290 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(291 + i * nn) + jIter * n * nn] = 1.0;
			buf[(292 + i * nn) + jIter * n * nn] = 1.0;
			buf[(293 + i * nn) + jIter * n * nn] = 1.0;
			buf[(294 + i * nn) + jIter * n * nn] = 1.0;
			buf[(295 + i * nn) + jIter * n * nn] = 1.0;
			buf[(296 + i * nn) + jIter * n * nn] = yTex;

			buf[(297 + i * nn) + jIter * n * nn] = xright;
			buf[(298 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(299 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(300 + i * nn) + jIter * n * nn] = 1.0;
			buf[(301 + i * nn) + jIter * n * nn] = 1.0;
			buf[(302 + i * nn) + jIter * n * nn] = 1.0;
			buf[(303 + i * nn) + jIter * n * nn] = 1.0;
			buf[(304 + i * nn) + jIter * n * nn] = 1.0;
			buf[(305 + i * nn) + jIter * n * nn] = yTex;

			buf[(306 + i * nn) + jIter * n * nn] = xleft;
			buf[(307 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(308 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(309 + i * nn) + jIter * n * nn] = 1.0;
			buf[(310 + i * nn) + jIter * n * nn] = 1.0;
			buf[(311 + i * nn) + jIter * n * nn] = 1.0;
			buf[(312 + i * nn) + jIter * n * nn] = 1.0;
			buf[(313 + i * nn) + jIter * n * nn] = 0.0;
			buf[(314 + i * nn) + jIter * n * nn] = yTex2;

			buf[(315 + i * nn) + jIter * n * nn] = xright;
			buf[(316 + i * nn) + jIter * n * nn] = 0.68 * Math.sin((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(317 + i * nn) + jIter * n * nn] = 0.68 * Math.cos((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(318 + i * nn) + jIter * n * nn] = 1.0;
			buf[(319 + i * nn) + jIter * n * nn] = 1.0;
			buf[(320 + i * nn) + jIter * n * nn] = 1.0;
			buf[(321 + i * nn) + jIter * n * nn] = 1.0;
			buf[(322 + i * nn) + jIter * n * nn] = 1.0;
			buf[(323 + i * nn) + jIter * n * nn] = yTex2;
		}
		jIter++;
  }
  console.log(buf.length)
  buf[buf.length] = -1.0
  buf[buf.length] = 1.0
  buf[buf.length] = 0.0
  buf[buf.length] = 1.0
  buf[buf.length] = 1.0
  buf[buf.length] = 1.0
  buf[buf.length] = 1.0
  buf[buf.length] = 1.0//0
  buf[buf.length] = 1.0//0
    
  buf[buf.length] =-1.0 
  buf[buf.length] =-1.0
  buf[buf.length] =0.0
  buf[buf.length] =1.0
  buf[buf.length] =1.0
  buf[buf.length] =1.0
  buf[buf.length] =1.0
  buf[buf.length] =1.0//0
  buf[buf.length] =0.0//1
  
  buf[buf.length] =1.0
  buf[buf.length] =1.0
  buf[buf.length] =0.0
  buf[buf.length] =1.0
  buf[buf.length] =1.0
  buf[buf.length] =1.0
  buf[buf.length] =1.0 
  buf[buf.length] =0.0//1
  buf[buf.length] =1.0//0
            
  buf[buf.length] =1.0 
	buf[buf.length] =1.0
	buf[buf.length] =0.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0
	buf[buf.length] =0.0//1
	buf[buf.length] =1.0//0
	
  buf[buf.length] =-1.0
	buf[buf.length] =-1.0 
	buf[buf.length] =0.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0//0 
	buf[buf.length] =0.0//1
	
  buf[buf.length] =1.0
	buf[buf.length] =-1.0
	buf[buf.length] =0.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0
	buf[buf.length] =1.0
  buf[buf.length] =0.0//1
	buf[buf.length] =0.0//1
    
  var vertexTexCoordBuffer = gl.createBuffer();
  if (!vertexTexCoordBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexTexCoordBuffer);
  var bbuf = new Float32Array(buf)
  gl.bufferData(gl.ARRAY_BUFFER,bbuf, gl.STATIC_DRAW);
  var FSIZE = bbuf.BYTES_PER_ELEMENT;
  var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return -1;
  }
  gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, FSIZE * 9, 0);
  gl.enableVertexAttribArray(a_Position);
  var a_Color = gl.getAttribLocation(gl.program, 'a_Color');
  if (a_Color < 0) {
    console.log('Failed to get the storage location of a_Color');
    return -1;
  }
  gl.vertexAttribPointer(a_Color, 4, gl.FLOAT, false, FSIZE * 9, FSIZE * 3);
  gl.enableVertexAttribArray(a_Color);
  var a_TexCoord = gl.getAttribLocation(gl.program, 'a_TexCoord');
  if (a_TexCoord < 0) {
    console.log('Failed to get the storage location of a_TexCoord');
    return -1;
  }
  gl.vertexAttribPointer(a_TexCoord, 2, gl.FLOAT, false, FSIZE * 9, FSIZE * 7);
  gl.enableVertexAttribArray(a_TexCoord);
//end function
}
function requestCORSIfNotSameOrigin(img, url) {
  if ((new URL(url, window.location.href)).origin !== window.location.origin) {
    img.crossOrigin = "";
  }
}
function initTextures(gl) {
  var texturefon = gl.createTexture();
  if (!texturefon) {
    console.log('Failed to create the texture object');
    return false;
	}
	var u_Sampler = gl.getUniformLocation(gl.program, 'u_Sampler');
	if (!u_Sampler) {
		console.log('Failed to get the storage location of u_Sampler');
		return false;
	}
  var fon = new Image();
  if (!fon) {
    console.log('Failed to create the image object');
    return false;
  }
	requestCORSIfNotSameOrigin(fon, 'https://s6.imgcdn.dev/WSTpv.png');
	fon.crossOrigin = "anonymous";
	fon.onload = function () { loadTexture(gl, texturefon, u_Sampler, fon,0); };
	fon.src = 'https://s6.imgcdn.dev/WSTpv.png';
	LoadDrum(gl);
	return true;
}
function LoadDrum(gl) {
	var texturesdrum1, texturesdrum2, texturesdrum3, texturesdrum4, texturesdrum5, texturesdrum6, texturesdrum7,
		u_Sampler1, u_Sampler2, u_Sampler3, u_Sampler4, u_Sampler5, u_Sampler6, u_Sampler7
		, images1, images2, images3, images4, images5, images6, images7,
		paths1, paths2, paths3, paths4, paths5, paths6, paths7;
	paths1 = "https://s6.imgcdn.dev/WSkIV.png";//"auto1.png";//auto1
	paths2 = "https://s6.imgcdn.dev/WSQXh.png";//'auto2.png';//auto2
	paths3 = "https://s6.imgcdn.dev/WSsLo.png";//'auto3.png';//auto3
	paths4 = "https://s6.imgcdn.dev/WSnBK.png";//"auto4.png";//auto4
	paths5 = "https://s6.imgcdn.dev/WS56O.png";//"auto5.png";//auto5
	paths6 = "https://s6.imgcdn.dev/WSKln.png";//"bonus.png";//bonus
	paths7 = "https://s6.imgcdn.dev/WSPVg.png";//"wild.jpg";//wild

	texturesdrum1 = gl.createTexture();
	u_Sampler1 = gl.getUniformLocation(gl.program, 'u_Sampler');
	images1 = new Image();
	requestCORSIfNotSameOrigin(images1, paths1);
	images1.crossOrigin = "anonymous";
	images1.onload = function () { loadTexture(gl, texturesdrum1, u_Sampler1, images1, 1); };
	images1.src = paths1;



	texturesdrum2 = gl.createTexture();
	u_Sampler2 = gl.getUniformLocation(gl.program, 'u_Sampler');
	images2 = new Image();
	requestCORSIfNotSameOrigin(images2, paths2);
	images2.crossOrigin = "anonymous";
	images2.onload = function () { loadTexture(gl, texturesdrum2, u_Sampler2, images2, 2); };
	images2.src = paths2;



	texturesdrum3 = gl.createTexture();
	u_Sampler3 = gl.getUniformLocation(gl.program, 'u_Sampler');
	images3 = new Image();
	requestCORSIfNotSameOrigin(images3, paths3);
	images3.crossOrigin = "anonymous";
	images3.onload = function () { loadTexture(gl, texturesdrum3, u_Sampler3, images3, 3); };
	images3.src = paths3;



	texturesdrum4 = gl.createTexture();
	u_Sampler4 = gl.getUniformLocation(gl.program, 'u_Sampler');
	images4 = new Image();
	requestCORSIfNotSameOrigin(images4, paths4);
	images4.crossOrigin = "anonymous";
	images4.onload = function () { loadTexture(gl, texturesdrum4, u_Sampler4, images4, 4); };
	images4.src = paths4;


	texturesdrum5 = gl.createTexture();
	u_Sampler5 = gl.getUniformLocation(gl.program, 'u_Sampler');
	images5 = new Image();
	requestCORSIfNotSameOrigin(images5, paths5);
	images5.crossOrigin = "anonymous";
	images5.onload = function () { loadTexture(gl, texturesdrum5, u_Sampler5, images5, 5); };
	images5.src = paths5;


	texturesdrum6 = gl.createTexture();
	u_Sampler6 = gl.getUniformLocation(gl.program, 'u_Sampler');
	images6 = new Image();
	requestCORSIfNotSameOrigin(images6, paths6);
	images6.crossOrigin = "anonymous";
	images6.onload = function () { loadTexture(gl, texturesdrum6, u_Sampler6, images6, 6); };
	images6.src = paths6;


	texturesdrum7 = gl.createTexture();
	u_Sampler7 = gl.getUniformLocation(gl.program, 'u_Sampler');
	images7 = new Image();
	requestCORSIfNotSameOrigin(images7, paths7);
	images7.crossOrigin = "anonymous";
	images7.onload = function () { loadTexture(gl, texturesdrum7, u_Sampler7, images7, 7); };
	images7.src = paths7;
}
function loadTexture(gl, texture, u_Sampler, image,num) {
	gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
	switch (num) {
		case 0:
			{
				gl.activeTexture(gl.TEXTURE0);
				break;
			}
		case 1:
			{
				gl.activeTexture(gl.TEXTURE1);
				break;
			}
		case 2:
			{
				gl.activeTexture(gl.TEXTURE2);
				break;
			}
		case 3:
			{
				gl.activeTexture(gl.TEXTURE3);
				break;
			}
		case 4:
			{
				gl.activeTexture(gl.TEXTURE4);
				break;
			}
		case 5:
			{
				gl.activeTexture(gl.TEXTURE5);
				break;
			}
		case 6:
			{
				gl.activeTexture(gl.TEXTURE6);
				break;
			}
		case 7:
			{
				gl.activeTexture(gl.TEXTURE7);
				break;
			}
		default:
			{
				break;
			}
	}
	//gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, texture);
 
  
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
  
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, image);
	if (gl.getError())
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, imageID);
	if (gl.getError())
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGBA, gl.UNSIGNED_BYTE, imageID);
	if (gl.getError())
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGB, gl.UNSIGNED_BYTE, imageID);
	gl.uniform1i(u_Sampler, num);
	if (num > 0)
		texturesVec.push(texture);
	else
		texturefon_ = texture;
	switch (num) {
		case 0:
			{
				ready1 = true;
				break;
			}
		case 1:
			{
				ready2 = true;
				break;
			}
		case 2:
			{
				ready3 = true;
				break;
			}
		case 3:
			{
				ready4 = true;
				break;
			}
		case 4:
			{
				ready5 = true;
				break;
			}
		case 5:
			{
				ready6 = true;
				break;
			}
		case 6:
			{
				ready7 = true;
				break;
			}
		case 7:
			{
				ready8 = true;
				break;
			}
		default:
			{
				break;
			}
	}
}
function draw(gl, currentAngle, modelMatrix, u_ModelMatrix, u_ProjMatrix,projMatrix, nf) {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  gl.enable(gl.DEPTH_TEST);
  gl.uniformMatrix4fv(u_ProjMatrix, false, projMatrix.elements);
  if(startRotate)
    modelMatrix.setRotate(currentAngle, 1, 0, 0);
  gl.uniformMatrix4fv(u_ModelMatrix, false, modelMatrix.elements);
  var jj=-1;
  for(var j = 0; j < 5; j++)
	{
		gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[++jj]]);
		for (var i = 0 + j * n; i < n + j * n; i++)
			gl.drawArrays(gl.TRIANGLES, 36 * i, 6);
		gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[++jj]]);
		for (var i = 0 + j * n; i < n + j * n; i++)
			gl.drawArrays(gl.TRIANGLES, 36 * i + 6, 6);
		gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[++jj]]);
		for (var i = 0 + j * n; i < n + j * n; i++)
			gl.drawArrays(gl.TRIANGLES, 36 * i + 12, 6);
		gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[++jj]]);
		for (var i = 0 + j * n; i < n + j * n; i++)
			gl.drawArrays(gl.TRIANGLES, 36 * i + 18, 6);
		gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[++jj]]);
		for (var i = 0 + j * n; i < n + j * n; i++)
			gl.drawArrays(gl.TRIANGLES, 36 * i + 24, 6);
		gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[++jj]]);
		for (var i = 0 + j * n; i < n + j * n; i++)
			gl.drawArrays(gl.TRIANGLES, 36 * i + 30, 6);
	}
    modelMatrix.setRotate(0/*-currentAngle*/, 1, 0, 0);
    gl.uniformMatrix4fv(u_ModelMatrix, false, modelMatrix.elements);
	gl.bindTexture(gl.TEXTURE_2D, texturefon_);
	if (ready1 && ready2 && ready3 && ready4 && ready5 && ready6 && ready7 && ready8)
		gl.drawArrays(gl.TRIANGLES, 36*5*n, 6);
  }