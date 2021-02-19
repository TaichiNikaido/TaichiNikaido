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
 108;
 10.09867;-0.97846;-0.93600;,
 10.77067;-0.57446;-1.11600;,
 8.32067;-0.59246;-1.36000;,
 8.29267;-1.11846;-1.06600;,
 10.85067;0.03754;-1.19800;,
 8.35067;0.03754;-1.45800;,
 2.11267;-0.69646;-1.58600;,
 2.15267;-1.31046;-1.24200;,
 -0.29133;-0.76646;-1.45600;,
 0.38467;-1.24646;-1.18400;,
 2.07267;0.03754;-1.70200;,
 -0.39933;0.03754;-1.56400;,
 8.32067;0.66754;-1.36000;,
 2.11267;0.77154;-1.58600;,
 -0.29133;0.84154;-1.45600;,
 2.15267;1.38554;-1.24200;,
 0.38467;1.32154;-1.18400;,
 8.29267;1.19354;-1.06600;,
 10.77067;0.64954;-1.11600;,
 10.09867;1.05154;-0.93600;,
 10.77067;1.24754;-0.56400;,
 8.32067;1.51154;-0.58000;,
 10.85067;1.33754;0.00000;,
 8.35067;1.61954;0.00000;,
 2.11267;1.75754;-0.67800;,
 -0.29133;1.61554;-0.74200;,
 2.07267;1.88354;0.00000;,
 -0.39933;1.73354;0.00000;,
 8.32067;1.51154;0.58000;,
 2.11267;1.75754;0.67800;,
 -0.29133;1.61554;0.74200;,
 2.15267;1.38554;1.24200;,
 0.38467;1.32154;1.18400;,
 8.29267;1.19354;1.06600;,
 10.77067;1.24754;0.56400;,
 10.09867;1.05154;0.93600;,
 10.77067;0.64954;1.11600;,
 8.32067;0.66754;1.36000;,
 10.85067;0.03754;1.19800;,
 8.35067;0.03754;1.45800;,
 2.11267;0.77154;1.58600;,
 -0.29133;0.84154;1.45600;,
 2.07267;0.03754;1.70200;,
 -0.39933;0.03754;1.56400;,
 8.32067;-0.59246;1.36000;,
 2.11267;-0.69646;1.58600;,
 -0.29133;-0.76646;1.45600;,
 2.15267;-1.31046;1.24200;,
 0.38467;-1.24646;1.18400;,
 8.29267;-1.11846;1.06600;,
 10.77067;-0.57446;1.11600;,
 10.09867;-0.97846;0.93600;,
 10.77067;-1.17246;0.56400;,
 8.32067;-1.43646;0.58000;,
 10.85067;-1.26246;-0.00000;,
 8.35067;-1.54446;-0.00000;,
 2.11267;-1.68246;0.67800;,
 -0.29133;-1.54046;0.74200;,
 2.07267;-1.80846;-0.00000;,
 -0.39933;-1.65846;0.00000;,
 8.32067;-1.43646;-0.58000;,
 2.11267;-1.68246;-0.67800;,
 -0.29133;-1.54046;-0.74200;,
 2.15267;-1.31046;-1.24200;,
 0.38467;-1.24646;-1.18400;,
 8.29267;-1.11846;-1.06600;,
 10.77067;-1.17246;-0.56400;,
 10.09867;-0.97846;-0.93600;,
 -1.39933;-0.88246;-0.84800;,
 -0.29133;-1.54046;-0.74200;,
 -1.63133;-0.95046;0.00000;,
 -0.39933;-1.65846;0.00000;,
 -1.63133;0.03754;-0.91000;,
 -1.93533;0.03754;0.00000;,
 -1.39933;-0.88246;0.84800;,
 -0.29133;-1.54046;0.74200;,
 -0.29133;-0.76646;1.45600;,
 0.38467;-1.24646;1.18400;,
 -1.63133;0.03754;0.91000;,
 -0.39933;0.03754;1.56400;,
 -1.63133;1.02554;0.00000;,
 -1.39933;0.95554;0.84800;,
 -0.29133;0.84154;1.45600;,
 -0.29133;1.61554;0.74200;,
 0.38467;1.32154;1.18400;,
 -0.39933;1.73354;0.00000;,
 -1.39933;0.95554;-0.84800;,
 -0.29133;1.61554;-0.74200;,
 10.09867;-0.97846;0.93600;,
 10.77067;-0.57446;1.11600;,
 11.81267;-0.63646;0.62000;,
 10.77067;-1.17246;0.56400;,
 11.98267;-0.68646;-0.00000;,
 10.85067;-1.26246;-0.00000;,
 11.98267;0.03754;0.66800;,
 12.20667;0.03754;0.00000;,
 10.85067;0.03754;1.19800;,
 11.81267;-0.63646;-0.62000;,
 10.77067;-1.17246;-0.56400;,
 11.98267;0.03754;-0.66800;,
 11.98267;0.76154;0.00000;,
 11.81267;0.71154;-0.62000;,
 10.77067;1.24754;-0.56400;,
 10.85067;1.33754;0.00000;,
 10.77067;0.64954;1.11600;,
 11.81267;0.71154;0.62000;,
 10.77067;1.24754;0.56400;,
 10.09867;1.05154;0.93600;;
 
 80;
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;7,6,2,3;,
 4;9,8,6,7;,
 4;8,11,10,6;,
 4;6,10,5,2;,
 4;10,13,12,5;,
 4;11,14,13,10;,
 4;14,16,15,13;,
 4;13,15,17,12;,
 4;5,12,18,4;,
 4;12,17,19,18;,
 4;17,21,20,19;,
 4;21,23,22,20;,
 4;15,24,21,17;,
 4;16,25,24,15;,
 4;25,27,26,24;,
 4;24,26,23,21;,
 4;26,29,28,23;,
 4;27,30,29,26;,
 4;30,32,31,29;,
 4;29,31,33,28;,
 4;23,28,34,22;,
 4;28,33,35,34;,
 4;33,37,36,35;,
 4;37,39,38,36;,
 4;31,40,37,33;,
 4;32,41,40,31;,
 4;41,43,42,40;,
 4;40,42,39,37;,
 4;42,45,44,39;,
 4;43,46,45,42;,
 4;46,48,47,45;,
 4;45,47,49,44;,
 4;39,44,50,38;,
 4;44,49,51,50;,
 4;49,53,52,51;,
 4;53,55,54,52;,
 4;47,56,53,49;,
 4;48,57,56,47;,
 4;57,59,58,56;,
 4;56,58,55,53;,
 4;58,61,60,55;,
 4;59,62,61,58;,
 4;62,64,63,61;,
 4;61,63,65,60;,
 4;55,60,66,54;,
 4;60,65,67,66;,
 4;69,68,8,9;,
 4;71,70,68,69;,
 4;70,73,72,68;,
 4;68,72,11,8;,
 4;75,74,70,71;,
 4;77,76,74,75;,
 4;76,79,78,74;,
 4;74,78,73,70;,
 4;78,81,80,73;,
 4;79,82,81,78;,
 4;82,84,83,81;,
 4;81,83,85,80;,
 4;72,86,14,11;,
 4;73,80,86,72;,
 4;80,85,87,86;,
 4;86,87,16,14;,
 4;91,90,89,88;,
 4;93,92,90,91;,
 4;92,95,94,90;,
 4;90,94,96,89;,
 4;98,97,92,93;,
 4;0,1,97,98;,
 4;1,4,99,97;,
 4;97,99,95,92;,
 4;99,101,100,95;,
 4;4,18,101,99;,
 4;18,19,102,101;,
 4;101,102,103,100;,
 4;94,105,104,96;,
 4;95,100,105,94;,
 4;100,103,106,105;,
 4;105,106,107,104;;
 
 MeshMaterialList {
  25;
  80;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.208000;0.184000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.672000;0.624000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.024000;0.024000;0.024000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.112000;0.000000;0.008000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.288000;0.176000;0.176000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.168000;0.104000;0.152000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.400000;0.040000;0.040000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.504000;0.368000;0.368000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.672000;0.624000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.672000;0.624000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.672000;0.624000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.112000;0.000000;0.008000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184000;0.152000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.737255;0.718431;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\gsp025\\Desktop\\kao.png";
   }
  }
 }
 MeshNormals {
  82;
  0.150303;-0.672595;-0.724586;,
  -0.111698;-0.675487;-0.728863;,
  0.150143;0.672452;-0.724752;,
  -0.111882;0.675472;-0.728849;,
  0.150143;0.672452;0.724752;,
  -0.111882;0.675472;0.728849;,
  0.150303;-0.672595;0.724586;,
  -0.111698;-0.675487;0.728863;,
  0.284898;0.958558;0.000000;,
  -0.265882;0.000050;0.964006;,
  0.265673;-0.000000;0.964063;,
  -0.284075;-0.958802;0.000000;,
  0.284896;-0.958558;-0.000000;,
  -0.265882;0.000050;-0.964006;,
  0.265673;-0.000000;-0.964063;,
  -0.284371;0.958714;0.000000;,
  0.070426;-0.000000;-0.997517;,
  0.076293;0.997085;0.000000;,
  0.070426;-0.000000;0.997517;,
  0.076293;-0.997085;-0.000000;,
  -1.000000;0.000137;0.000000;,
  1.000000;0.000000;0.000000;,
  0.223916;0.386432;0.894725;,
  -0.209435;0.389822;0.896759;,
  -0.006841;-0.000000;0.999977;,
  -0.209267;-0.389797;0.896809;,
  0.000815;-0.681062;0.732225;,
  0.069574;-0.330898;0.941098;,
  0.070194;-0.679763;0.730065;,
  0.224096;-0.386129;0.894810;,
  0.073842;-0.923103;0.377397;,
  0.235181;-0.870264;0.432817;,
  -0.219389;-0.872022;0.437546;,
  -0.007553;-0.999971;-0.000000;,
  -0.219389;-0.872022;-0.437546;,
  0.073842;-0.923103;-0.377397;,
  0.235181;-0.870264;-0.432817;,
  -0.783264;-0.621689;0.000000;,
  -0.765608;0.000123;-0.643307;,
  -0.765608;0.000123;0.643307;,
  -0.783399;0.621519;-0.000000;,
  0.765925;-0.642929;-0.000000;,
  0.748520;-0.000000;0.663112;,
  0.748520;-0.000000;-0.663112;,
  0.765927;0.642928;0.000000;,
  0.070194;-0.679763;-0.730065;,
  0.069574;-0.330898;-0.941098;,
  0.224096;-0.386129;-0.894810;,
  0.000815;-0.681062;-0.732225;,
  -0.209267;-0.389797;-0.896809;,
  -0.006841;-0.000000;-0.999977;,
  -0.209435;0.389822;-0.896759;,
  0.000817;0.681062;-0.732225;,
  0.069634;0.331162;-0.941001;,
  0.070332;0.679635;-0.730171;,
  0.223916;0.386432;-0.894725;,
  0.073942;0.922927;-0.377808;,
  0.235043;0.870078;-0.433267;,
  -0.219648;0.871844;-0.437770;,
  -0.007553;0.999972;-0.000000;,
  -0.219648;0.871844;0.437770;,
  0.000817;0.681062;0.732225;,
  0.073942;0.922927;0.377808;,
  0.070332;0.679635;0.730171;,
  0.235043;0.870078;0.433267;,
  0.069634;0.331162;0.941001;,
  -0.003035;-0.330857;-0.943676;,
  -0.003035;0.330856;-0.943676;,
  -0.003388;0.926001;-0.377506;,
  -0.003388;0.926001;0.377506;,
  -0.003035;0.330856;0.943676;,
  -0.003035;-0.330857;0.943676;,
  -0.003390;-0.926001;0.377505;,
  -0.003390;-0.926001;-0.377505;,
  -0.596522;-0.549580;-0.584913;,
  -0.596522;-0.549580;0.584913;,
  -0.596603;0.549365;0.585032;,
  -0.596603;0.549365;-0.585032;,
  0.576759;-0.560201;0.594579;,
  0.576759;-0.560201;-0.594579;,
  0.576550;0.560301;-0.594687;,
  0.576550;0.560301;0.594687;;
  80;
  4;45,46,47,0;,
  4;46,16,14,47;,
  4;48,66,46,45;,
  4;1,49,66,48;,
  4;49,13,50,66;,
  4;66,50,16,46;,
  4;50,67,53,16;,
  4;13,51,67,50;,
  4;51,3,52,67;,
  4;67,52,54,53;,
  4;16,53,55,14;,
  4;53,54,2,55;,
  4;54,56,57,2;,
  4;56,17,8,57;,
  4;52,68,56,54;,
  4;3,58,68,52;,
  4;58,15,59,68;,
  4;68,59,17,56;,
  4;59,69,62,17;,
  4;15,60,69,59;,
  4;60,5,61,69;,
  4;69,61,63,62;,
  4;17,62,64,8;,
  4;62,63,4,64;,
  4;63,65,22,4;,
  4;65,18,10,22;,
  4;61,70,65,63;,
  4;5,23,70,61;,
  4;23,9,24,70;,
  4;70,24,18,65;,
  4;24,71,27,18;,
  4;9,25,71,24;,
  4;25,7,26,71;,
  4;71,26,28,27;,
  4;18,27,29,10;,
  4;27,28,6,29;,
  4;28,30,31,6;,
  4;30,19,12,31;,
  4;26,72,30,28;,
  4;7,32,72,26;,
  4;32,11,33,72;,
  4;72,33,19,30;,
  4;33,73,35,19;,
  4;11,34,73,33;,
  4;34,1,48,73;,
  4;73,48,45,35;,
  4;19,35,36,12;,
  4;35,45,0,36;,
  4;34,74,49,1;,
  4;11,37,74,34;,
  4;37,20,38,74;,
  4;74,38,13,49;,
  4;32,75,37,11;,
  4;7,25,75,32;,
  4;25,9,39,75;,
  4;75,39,20,37;,
  4;39,76,40,20;,
  4;9,23,76,39;,
  4;23,5,60,76;,
  4;76,60,15,40;,
  4;38,77,51,13;,
  4;20,40,77,38;,
  4;40,15,58,77;,
  4;77,58,3,51;,
  4;31,78,29,6;,
  4;12,41,78,31;,
  4;41,21,42,78;,
  4;78,42,10,29;,
  4;36,79,41,12;,
  4;0,47,79,36;,
  4;47,14,43,79;,
  4;79,43,21,41;,
  4;43,80,44,21;,
  4;14,55,80,43;,
  4;55,2,57,80;,
  4;80,57,8,44;,
  4;42,81,22,10;,
  4;21,44,81,42;,
  4;44,8,64,81;,
  4;81,64,4,22;;
 }
 MeshTextureCoords {
  108;
  0.375000;0.000000;,
  0.375000;0.062500;,
  0.437500;0.062500;,
  0.437500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.125000;,
  0.562500;0.062500;,
  0.562500;0.000000;,
  0.625000;0.062500;,
  0.625000;0.000000;,
  0.562500;0.125000;,
  0.625000;0.125000;,
  0.437500;0.187500;,
  0.562500;0.187500;,
  0.625000;0.187500;,
  0.562500;0.250000;,
  0.625000;0.250000;,
  0.437500;0.250000;,
  0.375000;0.187500;,
  0.375000;0.250000;,
  0.375000;0.312500;,
  0.437500;0.312500;,
  0.375000;0.375000;,
  0.437500;0.375000;,
  0.562500;0.312500;,
  0.625000;0.312500;,
  0.562500;0.375000;,
  0.625000;0.375000;,
  0.437500;0.437500;,
  0.562500;0.437500;,
  0.625000;0.437500;,
  0.562500;0.500000;,
  0.625000;0.500000;,
  0.437500;0.500000;,
  0.375000;0.437500;,
  0.375000;0.500000;,
  0.375000;0.562500;,
  0.437500;0.562500;,
  0.375000;0.625000;,
  0.437500;0.625000;,
  0.562500;0.562500;,
  0.625000;0.562500;,
  0.562500;0.625000;,
  0.625000;0.625000;,
  0.437500;0.687500;,
  0.562500;0.687500;,
  0.625000;0.687500;,
  0.562500;0.750000;,
  0.625000;0.750000;,
  0.437500;0.750000;,
  0.375000;0.687500;,
  0.375000;0.750000;,
  0.375000;0.812500;,
  0.437500;0.812500;,
  0.375000;0.875000;,
  0.437500;0.875000;,
  0.562500;0.812500;,
  0.625000;0.812500;,
  0.562500;0.875000;,
  0.625000;0.875000;,
  0.437500;0.937500;,
  0.562500;0.937500;,
  0.625000;0.937500;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.437500;1.000000;,
  0.375000;0.937500;,
  0.375000;1.000000;,
  0.687500;0.062500;,
  0.687500;0.000000;,
  0.750000;0.062500;,
  0.750000;0.000000;,
  0.687500;0.125000;,
  0.750000;0.125000;,
  0.812500;0.062500;,
  0.812500;0.000000;,
  0.875000;0.062500;,
  0.875000;0.000000;,
  0.812500;0.125000;,
  0.875000;0.125000;,
  0.750000;0.187500;,
  0.812500;0.187500;,
  0.875000;0.187500;,
  0.812500;0.250000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.687500;0.187500;,
  0.687500;0.250000;,
  0.125000;0.000000;,
  0.125000;0.062500;,
  0.187500;0.062500;,
  0.187500;0.000000;,
  0.250000;0.062500;,
  0.250000;0.000000;,
  0.187500;0.125000;,
  0.250000;0.125000;,
  0.125000;0.125000;,
  0.312500;0.062500;,
  0.312500;0.000000;,
  0.312500;0.125000;,
  0.250000;0.187500;,
  0.312500;0.187500;,
  0.312500;0.250000;,
  0.250000;0.250000;,
  0.125000;0.187500;,
  0.187500;0.187500;,
  0.187500;0.250000;,
  0.125000;0.250000;;
 }
}
