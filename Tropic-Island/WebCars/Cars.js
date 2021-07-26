// RotatingTriangle.js (c) 2012 matsuda
// Vertex shader program
var VSHADER_SOURCE =
  'attribute vec4 a_Position;\n' +
  'uniform mat4 u_ProjMatrix;\n' +
  'uniform mat4 u_ModelMatrix;\n' +
  'void main() {\n' +
  '  gl_Position = u_ProjMatrix * u_ModelMatrix * a_Position;\n' +
  '}\n';

// Fragment shader program
var FSHADER_SOURCE =
'precision mediump float;\n' +
'uniform vec4 u_FragColor;\n' + // uniform-переменная
  'void main() {\n' +
' gl_FragColor = u_FragColor;\n' +
  //'  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' +
  '}\n';

// Rotation angle (degrees/second)
var ANGLE_STEP = -720.0;
var startRotate = 0;
var g_colors = [];
function main() {
  // Retrieve <canvas> element
  var canvas = document.getElementById('webgl');
var nf = document.getElementById('nearFar');

  // Get the rendering context for WebGL
  var gl = getWebGLContext(canvas);
  if (!gl) {
    console.log('Failed to get the rendering context for WebGL');
    return;
  }

  // Initialize shaders
  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    console.log('Failed to intialize shaders.');
    return;
  }

  // Write the positions of vertices to a vertex shader

  var n = initVertexBuffers(gl);

  if (n < 0) {
    console.log('Failed to set the positions of the vertices');
    return;
  }

  // Specify the color for clearing <canvas>
  gl.clearColor(0.0, 0.0, 0.0, 1.0);

  // Get storage location of u_ModelMatrix
  var u_ModelMatrix = gl.getUniformLocation(gl.program, 'u_ModelMatrix');
  if (!u_ModelMatrix) {
    console.log('Failed to get the storage location of u_ModelMatrix');
    return;
  }

  // Current rotation angle
  var currentAngle = 0.0;
  // Model matrix
  var modelMatrix = new Matrix4();

  // Получить ссылку на переменную u_ProjMatrix
  var u_ProjMatrix = gl.getUniformLocation(gl.program,'u_ProjMatrix');

  // Создать матрицу для установки местоположения точки наблюдения
  var projMatrix = new Matrix4();

var u_FragColor = gl.getUniformLocation(gl.program, 'u_FragColor');
  // Start drawing
  var tick = function() {
    currentAngle = animate(currentAngle);  // Update the rotation angle
    console.log(currentAngle);
    if (currentAngle<=-1800 ) {
      startRotate=!startRotate;
      currentAngle = 0.0;
    }
    draw(gl, n, currentAngle, modelMatrix, u_ModelMatrix,u_FragColor,n, u_ProjMatrix,
 projMatrix, nf);   // Draw the triangle
    requestAnimationFrame(tick, canvas); // Request that the browser calls tick
  };
  tick();

  canvas.onmousedown = function(ev) { click(ev, gl, canvas,u_FragColor); };
}
var nn = 120;
function initVertexBuffers(gl) {
  var vertices =

  new Float32Array ([
  //-0.5, 0.5,  -0.5,-0.5,  0.5, 0.5,  0.5, -0.5,
  -0.78,0.68,0.0, -0.78,0.3,0.6, -0.48,0.68,0.0, -0.48,0.3,0.6,
  -0.78,0.3,0.6, -0.78,-0.3,0.6, -0.48,0.3,0.6, -0.48,-0.3,0.6,
  -0.78,-0.3,0.6, -0.78,-0.68,0.0, -0.48,-0.3,0.6,   -0.48,-0.68,0.0,

  -0.78,0.68,0.0, -0.78,0.3,-0.6, -0.48,0.68,0.0, -0.48,0.3,-0.6,
  -0.78,0.3,-0.6, -0.78,-0.3,-0.6, -0.48,0.3,-0.6, -0.48,-0.3,-0.6,
  -0.78,-0.3,-0.6, -0.78,-0.68,0.0, -0.48,-0.3,-0.6,   -0.48,-0.68,0.0,

  -0.48,0.68,0.0, -0.48,0.3,0.6, -0.16,0.68,0.0, -0.16,0.3,0.6,
  -0.48,0.3,0.6, -0.48,-0.3,0.6, -0.16,0.3,0.6, -0.16,-0.3,0.6,
  -0.48,-0.3,0.6, -0.48,-0.68,0.0, -0.16,-0.3,0.6,   -0.16,-0.68,0.0,

  -0.48,0.68,0.0, -0.48,0.3,-0.6, -0.16,0.68,0.0, -0.16,0.3,-0.6,
  -0.48,0.3,-0.6, -0.48,-0.3,-0.6, -0.16,0.3,-0.6, -0.16,-0.3,-0.6,
  -0.48,-0.3,-0.6, -0.48,-0.68,0.0, -0.16,-0.3,-0.6,   -0.16,-0.68,0.0,



    -0.16,0.68,0.0, -0.16,0.3,0.6, 0.16,0.68,0.0, 0.16,0.3,0.6,
    -0.16,0.3,0.6, -0.16,-0.3,0.6, 0.16,0.3,0.6, 0.16,-0.3,0.6,
    -0.16,-0.3,0.6, -0.16,-0.68,0.0, 0.16,-0.3,0.6,   0.16,-0.68,0.0,

    -0.16,0.68,0.0, -0.16,0.3,-0.6, 0.16,0.68,0.0, 0.16,0.3,-0.6,
    -0.16,0.3,-0.6, -0.16,-0.3,-0.6, 0.16,0.3,-0.6, 0.16,-0.3,-0.6,
    -0.16,-0.3,-0.6, -0.16,-0.68,0.0, 0.16,-0.3,-0.6,   0.16,-0.68,0.0,


    0.16,0.68,0.0, 0.16,0.3,0.6, 0.48,0.68,0.0, 0.48,0.3,0.6,
    0.16,0.3,0.6, 0.16,-0.3,0.6, 0.48,0.3,0.6, 0.48,-0.3,0.6,
    0.16,-0.3,0.6, 0.16,-0.68,0.0, 0.48,-0.3,0.6,   0.48,-0.68,0.0,

    0.16,0.68,0.0, 0.16,0.3,-0.6, 0.48,0.68,0.0, 0.48,0.3,-0.6,
    0.16,0.3,-0.6, 0.16,-0.3,-0.6, 0.48,0.3,-0.6, 0.48,-0.3,-0.6,
    0.16,-0.3,-0.6, 0.16,-0.68,0.0, 0.48,-0.3,-0.6,   0.48,-0.68,0.0,


    0.48,0.68,0.0, 0.48,0.3,0.6, 0.78,0.68,0.0, 0.78,0.3,0.6,
    0.48,0.3,0.6, 0.48,-0.3,0.6, 0.78,0.3,0.6, 0.78,-0.3,0.6,
    0.48,-0.3,0.6, 0.48,-0.68,0.0, 0.78,-0.3,0.6,   0.78,-0.68,0.0,

    0.48,0.68,0.0, 0.48,0.3,-0.6, 0.78,0.68,0.0, 0.78,0.3,-0.6,
    0.48,0.3,-0.6, 0.48,-0.3,-0.6, 0.78,0.3,-0.6, 0.78,-0.3,-0.6,
    0.48,-0.3,-0.6, 0.48,-0.68,0.0, 0.78,-0.3,-0.6,   0.78,-0.68,0.0



  ]);

  var n = 4;   // The number of vertices
/*
  xl = -0.78;
  xr = -0.48;
  yd = 0.3;
  yu = 0.68;
*/


  // Create a buffer object
  var vertexBuffer = gl.createBuffer();
  if (!vertexBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  // Bind the buffer object to target
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  // Write date into the buffer object
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);


  // Assign the buffer object to a_Position variable
  var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if(a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return -1;
  }
  gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, 0, 0);

  // Enable the assignment to a_Position variable
  gl.enableVertexAttribArray(a_Position);

  return n;
}

function draw(gl, n, currentAngle, modelMatrix, u_ModelMatrix,u_FragColor,n, u_ProjMatrix,
 projMatrix, nf) {
   var g_near = -2.0, g_far = 2.0;
  // Set the rotation matrix
  if(startRotate)
    modelMatrix.setRotate(currentAngle, 1, 0, 0);
    //  modelMatrix.setRotate(currentAngle, 0, 1, 0); // Rotation angle, rotation axis (0, 0, 1)

  // Pass the rotation matrix to the vertex shader
  gl.uniformMatrix4fv(u_ModelMatrix, false, modelMatrix.elements);
projMatrix.setOrtho(-2, 2, -2, 2, g_near, g_far);
gl.uniformMatrix4fv(u_ProjMatrix, false, projMatrix.elements);
  // Clear <canvas>
  gl.clear(gl.COLOR_BUFFER_BIT);
  var i=0;
  for(i,j=0;i<nn;i+=4,j++)
  {
    g_colors.push([Math.random(), Math.random(), Math.random(), 1.0]);
var rgba = g_colors[j];
gl.uniform4f(u_FragColor, rgba[0],rgba[1],rgba[2],rgba[3]);
// Вывести текущие значения near и far
nf.innerHTML = 'near: ' + g_near + ', far: ' +
g_far;
  // Draw the rectangle
    gl.drawArrays(gl.TRIANGLE_STRIP, i, n);
    //gl.drawArrays(gl.TRIANGLE_STRIP, 4, n);
  }
}


// Last time that this function was called
var g_last = Date.now();
function animate(angle) {



  // Calculate the elapsed time
  var now = Date.now();
  var elapsed = now - g_last;
  g_last = now;
    //var newAngle=0;
  if (startRotate) {
  // Update the current rotation angle (adjusted by the elapsed time)
   angle-=30;//= angle + (ANGLE_STEP * elapsed) / 1000.0;
}
  return angle ;//%= 360;
}
function click(ev, gl, canvas,u_FragColor) {
  //alert(' Thanks a million!');
  startRotate = !startRotate;
}
