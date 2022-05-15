// TexturedQuad.js (c) 2012 matsuda and kanda
// Vertex shader program
var VSHADER_SOURCE =
  'attribute vec4 a_Position;\n' +
  'attribute vec2 a_TexCoord;\n' +
  'varying vec2 v_TexCoord;\n' +
  'uniform mat4 u_ProjMatrix;\n' +
  'uniform mat4 u_ModelMatrix;\n' +
  'void main() {\n' +
  '  gl_Position = u_ProjMatrix * u_ModelMatrix * a_Position;\n' +
  '  v_TexCoord = a_TexCoord;\n' +
  '}\n';

// Fragment shader program
var FSHADER_SOURCE =
  '#ifdef GL_ES\n' +
  'precision mediump float;\n' +
  '#endif\n' +
  'uniform sampler2D u_Sampler;\n' +
  'varying vec2 v_TexCoord;\n' +
  'void main() {\n' +
  '  gl_FragColor = texture2D(u_Sampler, v_TexCoord);\n' +
  '}\n';
// Rotation angle (degrees/second)
var ANGLE_STEP = -720.0;
var startRotate = 0;
var texturesVec=[],Drum=[];
function main() {
  min=0;
  max=1;
  for(var i=0;i<18;i++)
  {
    min = Math.ceil(min);
    max = Math.floor(max);
    Drum.push(Math.floor(Math.random() * (max - min + 1)) + min);
   // console.log(Drum[i]);
  }
  // Retrieve <canvas> element
  var canvas = document.getElementById('c');
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

  // Set the vertex information
  var n = initVertexBuffers(gl);
  if (n < 0) {
    console.log('Failed to set the vertex information');
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


  //gl.depthFunc(gl.LEQUAL);
  // Set texture
  if (!initTextures(gl, n)) {
    console.log('Failed to intialize the texture.');
    return;
  }
  
    // Start drawing
 var tick = function() {
    currentAngle = animate(currentAngle);  // Update the rotation angle
   // console.log(currentAngle);
    if (currentAngle>=1820 ) {
      startRotate=!startRotate;
      currentAngle = 0.0;
    }
    draw(gl, n, currentAngle, modelMatrix, u_ModelMatrix, u_ProjMatrix,projMatrix, nf);   // Draw the triangle
    requestAnimationFrame(tick, canvas); // Request that the browser calls tick
  };
  tick();

  canvas.onmousedown = function(ev) { click(ev, gl, canvas); };
  
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
   angle+=20;//= angle + (ANGLE_STEP * elapsed) / 1000.0;
}
  return angle ;//%= 360;
}
function click(ev, gl, canvas) {
  //alert(' Thanks a million!');
  startRotate = !startRotate;
/*  tmp = texturesVec[0];
  texturesVec[0] = texturesVec[1];
  texturesVec[1]=tmp;*/
  Drum=[];
  min=0;
  max=1;
  for(var i=0;i<18;i++)
  {
    min = Math.ceil(min);
    max = Math.floor(max);
    Drum.push(Math.floor(Math.random() * (max - min + 1)) + min);
   // console.log(Drum[i]);
  }
}
function initVertexBuffers(gl) {
  var verticesTexCoords = new Float32Array([
    // Vertex coordinates, texture coordinate
    //left up
    -0.48,  0.68,0.0,   0.0, 1.0,
    -0.48,  0.3,0.6,   0.0, 0.0,
     -0.16,  0.68,0.0,   1.0, 1.0,
    
    -0.16,  0.68,0.0,   1.0, 1.0,
     -0.16,  0.3,0.6, 1.0, 0.0,
    -0.48, 0.3,0.6, 0.0, 0.0,
    //reflection left up
    -0.48,  0.68,0.0,   0.0, 1.0,
    -0.48,  0.3,-0.6,   0.0, 0.0,
     -0.16,  0.68,0.0,   1.0, 1.0,
    
    -0.16,  0.68,0.0,   1.0, 1.0,
     -0.16,  0.3,-0.6, 1.0, 0.0,
    -0.48, 0.3,-0.6, 0.0, 0.0,
   
    //left middle
    -0.48,  0.3,0.6,   0.0, 1.0,
    -0.48,  -0.3,0.6,   0.0, 0.0,
     -0.16,  0.3,0.6,   1.0, 1.0,
    
    -0.16,  0.3,0.6,   1.0, 1.0,
     -0.16,  -0.3,0.6, 1.0, 0.0,
    -0.48, -0.3,0.6, 0.0, 0.0,
     //reflection middle left
    -0.48,  0.3,-0.6,   0.0, 1.0,
    -0.48,  -0.3,-0.6,   0.0, 0.0,
     -0.16,  0.3,-0.6,   1.0, 1.0,
    
    -0.16,  0.3,-0.6,   1.0, 1.0,
     -0.16,  -0.3,-0.6, 1.0, 0.0,
    -0.48, -0.3,-0.6, 0.0, 0.0,
    //down left
     -0.48,  -0.3,0.6,   0.0, 1.0,
    -0.48,  -0.68,0.0,   0.0, 0.0,
     -0.16,  -0.3,0.6,   1.0, 1.0,
    
    -0.16,  -0.3,0.6,   1.0, 1.0,
     -0.16,  -0.68,0.0, 1.0, 0.0,
    -0.48, -0.68,0.0, 0.0, 0.0,
     //reflection down left
     -0.48,  -0.3,-0.6,   0.0, 1.0,
    -0.48,  -0.68,0.0,   0.0, 0.0,
     -0.16,  -0.3,-0.6,   1.0, 1.0,
    
    -0.16,  -0.3,-0.6,   1.0, 1.0,
     -0.16,  -0.68,0.0, 1.0, 0.0,
    -0.48, -0.68,0.0, 0.0, 0.0,
    //center up
        -0.16,  0.68,0.0,   0.0, 1.0,
    -0.16,  0.3,0.6,   0.0, 0.0,
     0.16,  0.68,0.0,   1.0, 1.0,
    
    0.16,  0.68,0.0,   1.0, 1.0,
     0.16,  0.3,0.6, 1.0, 0.0,
    -0.16, 0.3,0.6, 0.0, 0.0,
    //reflection center up
        -0.16,  0.68,0.0,   0.0, 1.0,
    -0.16,  0.3,-0.6,   0.0, 0.0,
     0.16,  0.68,0.0,   1.0, 1.0,
    
    0.16,  0.68,0.0,   1.0, 1.0,
     0.16,  0.3,-0.6, 1.0, 0.0,
    -0.16, 0.3,-0.6, 0.0, 0.0,
    //middle center
    -0.16,  0.3,0.6,   0.0, 1.0,
    -0.16,  -0.3,0.6,   0.0, 0.0,
     0.16,  0.3,0.6,   1.0, 1.0,
    
    0.16,  0.3,0.6,   1.0, 1.0,
     0.16,  -0.3,0.6, 1.0, 0.0,
    -0.16, -0.3,0.6, 0.0, 0.0,
    //reflection middle center 
     -0.16,  0.3,-0.6,   0.0, 1.0,
    -0.16,  -0.3,-0.6,   0.0, 0.0,
     0.16,  0.3,-0.6,   1.0, 1.0,
    
    0.16,  0.3,-0.6,   1.0, 1.0,
     0.16,  -0.3,-0.6, 1.0, 0.0,
    -0.16, -0.3,-0.6, 0.0, 0.0,
    //down center
    -0.16,  -0.3,0.6,   0.0, 1.0,
    -0.16,  -0.68,0.0,   0.0, 0.0,
     0.16,  -0.3,0.6,   1.0, 1.0,
    
    0.16,  -0.3,0.6,   1.0, 1.0,
     0.16,  -0.68,0.0, 1.0, 0.0,
    -0.16, -0.68,0.0, 0.0, 0.0,
    //reflect down center
    -0.16,  -0.3,-0.6,   0.0, 1.0,
    -0.16,  -0.68,0.0,   0.0, 0.0,
     0.16,  -0.3,-0.6,   1.0, 1.0,
    
    0.16,  -0.3,-0.6,   1.0, 1.0,
     0.16,  -0.68,0.0, 1.0, 0.0,
    -0.16, -0.68,0.0, 0.0, 0.0,
    //////////////////////////
    //
     //right up
    0.16,  0.68,0.0,   0.0, 1.0,
    0.16,  0.3,0.6,   0.0, 0.0,
    0.48,  0.68,0.0,   1.0, 1.0,
    
    0.48,  0.68,0.0,   1.0, 1.0,
    0.48,  0.3,0.6, 1.0, 0.0,
    0.16, 0.3,0.6, 0.0, 0.0,
    //reflection right up
    0.16,  0.68,0.0,   0.0, 1.0,
    0.16,  0.3,-0.6,   0.0, 0.0,
    0.48,  0.68,0.0,   1.0, 1.0,
    
    0.48,  0.68,0.0,   1.0, 1.0,
    0.48,  0.3,-0.6, 1.0, 0.0,
    0.16, 0.3,-0.6, 0.0, 0.0,
   
    //right middle
    0.16,  0.3,0.6,   0.0, 1.0,
    0.16,  -0.3,0.6,   0.0, 0.0,
    0.48,  0.3,0.6,   1.0, 1.0,
    
    0.48,  0.3,0.6,   1.0, 1.0,
    0.48,  -0.3,0.6, 1.0, 0.0,
    0.16, -0.3,0.6, 0.0, 0.0,
     //reflection middle right
    0.16,  0.3,-0.6,   0.0, 1.0,
    0.16,  -0.3,-0.6,   0.0, 0.0,
     0.48,  0.3,-0.6,   1.0, 1.0,
    
    0.48,  0.3,-0.6,   1.0, 1.0,
    0.48,  -0.3,-0.6, 1.0, 0.0,
    0.16, -0.3,-0.6, 0.0, 0.0,
    //down right
    0.16,  -0.3,0.6,   0.0, 1.0,
    0.16,  -0.68,0.0,   0.0, 0.0,
     0.48,  -0.3,0.6,   1.0, 1.0,
    
    0.48,  -0.3,0.6,   1.0, 1.0,
    0.48,  -0.68,0.0, 1.0, 0.0,
    0.16, -0.68,0.0, 0.0, 0.0,
     //reflection down right
    0.16,  -0.3,-0.6,   0.0, 1.0,
    0.16,  -0.68,0.0,   0.0, 0.0,
    0.48,  -0.3,-0.6,   1.0, 1.0,
    
    0.48,  -0.3,-0.6,   1.0, 1.0,
     0.48,  -0.68,0.0, 1.0, 0.0,
    0.16, -0.68,0.0, 0.0, 0.0,
  ]);
  var n = 6; // The number of vertices

  // Create the buffer object
  
  var vertexTexCoordBuffer = gl.createBuffer();
  if (!vertexTexCoordBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  // Bind the buffer object to target
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexTexCoordBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, verticesTexCoords, gl.STATIC_DRAW);

  var FSIZE = verticesTexCoords.BYTES_PER_ELEMENT;
  //Get the storage location of a_Position, assign and enable buffer
  var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return -1;
  }
  gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, FSIZE * 5, 0);
  gl.enableVertexAttribArray(a_Position);  // Enable the assignment of the buffer object

  // Get the storage location of a_TexCoord
  var a_TexCoord = gl.getAttribLocation(gl.program, 'a_TexCoord');
  if (a_TexCoord < 0) {
    console.log('Failed to get the storage location of a_TexCoord');
    return -1;
  }
  // Assign the buffer object to a_TexCoord variable
  gl.vertexAttribPointer(a_TexCoord, 2, gl.FLOAT, false, FSIZE * 5, FSIZE * 3);
  gl.enableVertexAttribArray(a_TexCoord);  // Enable the assignment of the buffer object

  return n;
}
function requestCORSIfNotSameOrigin(img, url) {
  if ((new URL(url, window.location.href)).origin !== window.location.origin) {
    img.crossOrigin = "";
  }
}
function initTextures(gl, n) {
  var texture = gl.createTexture();   // Create a texture object
  if (!texture) {
    console.log('Failed to create the texture object');
    return false;
  }
 var texture2 = gl.createTexture();   // Create a texture object
  if (!texture2) {
    console.log('Failed to create the texture object');
    return false;
  }
  // Get the storage location of u_Sampler
  var u_Sampler = gl.getUniformLocation(gl.program, 'u_Sampler');
  if (!u_Sampler) {
    console.log('Failed to get the storage location of u_Sampler');
    return false;
  }
  var image = new Image();  // Create the image object
  if (!image) {
    console.log('Failed to create the image object');
    return false;
  }
  var image2 = new Image();  // Create the image object
  if (!image2) {
    console.log('Failed to create the image object');
    return false;
  }
  requestCORSIfNotSameOrigin(image, 'https://webglfundamentals.org/webgl/resources/f-texture.png');
  requestCORSIfNotSameOrigin(image2,'https://webglfundamentals.org/webgl/resources/star.jpg' 
                             //'https://webglfundamentals.org/webgl/resources/mip-low-res-example.png'
);
  // Register the event handler to be called on loading an image
  image.onload = function(){ loadTexture(gl, 0,n, texture, u_Sampler, image); };
  // Tell the browser to load an image
  image.src = 'https://webglfundamentals.org/webgl/resources/star.jpg';//'https://webglfundamentals.org/webgl/resources/mip-low-res-example.png';
  // Register the event handler to be called on loading an image
  image2.onload = function(){ loadTexture(gl, n,n, texture2, u_Sampler, image2); };
  // Tell the browser to load an image
  image2.src ='https://webglfundamentals.org/webgl/resources/f-texture.png';
  return true;
}


function loadTexture(gl,offset, n, texture, u_Sampler, image) {
  gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1); // Flip the image's y axis
  // Enable texture unit0
  gl.activeTexture(gl.TEXTURE0);
  // Bind the texture object to the target
  
  gl.bindTexture(gl.TEXTURE_2D, texture);
  texturesVec.push(texture);
  // Set the texture parameters
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
     gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
     gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
  //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
  // Set the texture image
  gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, image);
  
  // Set the texture unit 0 to the sampler
  gl.uniform1i(u_Sampler, 0);
  
  //gl.clear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);   // Clear <canvas>

  //gl.drawArrays(gl.TRIANGLES, 0+offset, n); // Draw the rectangle
}
function draw(gl, n, currentAngle, modelMatrix, u_ModelMatrix, u_ProjMatrix,projMatrix, nf) {
   var g_near = -1.0, g_far = 1.0;
  // Set the rotation matrix
  if(startRotate)
    modelMatrix.setRotate(currentAngle, 1, 0, 0);
    //  modelMatrix.setRotate(currentAngle, 0, 1, 0); // Rotation angle, rotation axis (0, 0, 1)
  // Pass the rotation matrix to the vertex shader
  gl.uniformMatrix4fv(u_ModelMatrix, false, modelMatrix.elements);
  projMatrix.setOrtho(-1, 1, -1, 1, g_near, g_far);
  gl.uniformMatrix4fv(u_ProjMatrix, false, projMatrix.elements);
  // Clear <canvas>
  gl.clear(gl.GL_COLOR_BUFFER_BIT);
  // Вывести текущие значения near и far
  nf.innerHTML = 'near: ' + g_near + ', far: ' +
  g_far;
  //Draw the drum
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    //gl.enable(gl.CULL_FACE);
  gl.enable(gl.DEPTH_TEST);
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[0]]);//
   gl.drawArrays(gl.TRIANGLES, 0, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[1]]);//
   gl.drawArrays(gl.TRIANGLES, n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[2]]);
   gl.drawArrays(gl.TRIANGLES, 2*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[3]]);
   gl.drawArrays(gl.TRIANGLES, 3*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[4]]);
   gl.drawArrays(gl.TRIANGLES, 4*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[5]]);
   gl.drawArrays(gl.TRIANGLES, 5*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[6]]);
   gl.drawArrays(gl.TRIANGLES, 6*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[7]]);
   gl.drawArrays(gl.TRIANGLES, 7*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[8]]);
   gl.drawArrays(gl.TRIANGLES, 8*n, n);
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[9]]);
   gl.drawArrays(gl.TRIANGLES, 9*n, n);
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[10]]);
   gl.drawArrays(gl.TRIANGLES, 10*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[11]]);
   gl.drawArrays(gl.TRIANGLES, 11*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[12]]);
   gl.drawArrays(gl.TRIANGLES, 12*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[13]]);
   gl.drawArrays(gl.TRIANGLES, 13*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[14]]);
   gl.drawArrays(gl.TRIANGLES, 14*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[15]]);
   gl.drawArrays(gl.TRIANGLES, 15*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[16]]);
   gl.drawArrays(gl.TRIANGLES, 16*n, n); 
  gl.bindTexture(gl.TEXTURE_2D, texturesVec[Drum[17]]);
   gl.drawArrays(gl.TRIANGLES, 17*n, n); 
}
