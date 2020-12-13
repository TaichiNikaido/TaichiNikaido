xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 24;
 -139.70000;190.00000;-77.90000;,
 139.70000;190.00000;-77.90000;,
 149.70000;0.00000;-77.90000;,
 -149.70000;0.00000;-77.90000;,
 139.70000;200.00000;-67.90000;,
 139.70000;190.00000;-77.90000;,
 -139.70000;190.00000;-77.90000;,
 -139.70000;200.00000;-67.90000;,
 149.70000;0.00000;-77.90000;,
 149.70000;190.00000;-67.90000;,
 -149.70000;190.00000;-67.90000;,
 -139.70000;200.00000;-67.90000;,
 149.70000;190.00000;67.90000;,
 149.70000;0.00000;77.90000;,
 139.70000;200.00000;67.90000;,
 139.70000;190.00000;77.90000;,
 -139.70000;190.00000;77.90000;,
 -149.70000;0.00000;77.90000;,
 -139.70000;200.00000;67.90000;,
 -149.70000;190.00000;67.90000;,
 -139.70000;200.00000;67.90000;,
 139.70000;200.00000;67.90000;,
 139.70000;200.00000;-67.90000;,
 -139.70000;200.00000;-67.90000;;
 
 17;
 4;0,1,2,3;,
 4;4,5,6,7;,
 3;8,5,9;,
 3;10,0,3;,
 3;10,11,0;,
 3;4,9,5;,
 4;9,12,13,8;,
 4;14,12,9,4;,
 3;13,12,15;,
 3;14,15,12;,
 4;15,16,17,13;,
 4;18,16,15,14;,
 3;17,16,19;,
 3;18,19,16;,
 4;19,10,3,17;,
 4;11,10,19,18;,
 4;20,21,22,23;;
 
 MeshMaterialList {
  3;
  17;
  2,
  2,
  2,
  2,
  2,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  2,
  2,
  2,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data\\Material\\Cloth.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data\\Material\\Cloth.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
     "Data\\Material\\Cloth.jpg";
   }
  }
 }
 MeshNormals {
  19;
  -0.382473;0.020130;-0.923747;,
  0.382473;0.020130;-0.923747;,
  0.923747;0.020130;0.382473;,
  -0.382473;0.020130;0.923747;,
  -0.365480;0.376206;-0.851407;,
  0.365480;0.376206;-0.851407;,
  0.851407;0.376206;-0.365480;,
  0.851407;0.376206;0.365480;,
  0.365480;0.376206;0.851407;,
  -0.365480;0.376206;0.851407;,
  -0.851407;0.376206;0.365480;,
  -0.851407;0.376206;-0.365480;,
  -0.367001;0.854763;0.367001;,
  0.367001;0.854763;0.367001;,
  0.367001;0.854763;-0.367001;,
  -0.367001;0.854763;-0.367001;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;;
  17;
  4;4,5,1,0;,
  4;14,5,4,15;,
  3;1,5,6;,
  3;11,4,0;,
  3;11,15,4;,
  3;14,6,5;,
  4;6,7,2,16;,
  4;13,7,6,14;,
  3;2,7,8;,
  3;13,8,7;,
  4;8,9,3,17;,
  4;12,9,8,13;,
  3;3,9,10;,
  3;12,10,9;,
  4;10,11,18,18;,
  4;15,11,10,12;,
  4;12,13,14,15;;
 }
 MeshTextureCoords {
  24;
  0.830960;0.222740;,
  1.169040;0.222740;,
  1.173640;0.500000;,
  0.826360;0.500000;,
  0.178000;0.210190;,
  0.169040;0.222740;,
  -0.169040;0.222740;,
  -0.178000;0.210190;,
  0.173640;0.500000;,
  0.182230;0.227030;,
  0.817770;0.227030;,
  0.822000;0.210190;,
  0.317770;0.227030;,
  0.326360;0.500000;,
  0.322000;0.210190;,
  0.330960;0.222740;,
  0.669040;0.222740;,
  0.673640;0.500000;,
  0.678000;0.210190;,
  0.682230;0.227030;,
  0.677995;0.210190;,
  0.322005;0.210190;,
  0.177995;0.210190;,
  0.822005;0.210190;;
 }
}
