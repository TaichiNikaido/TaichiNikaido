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
 114;
 0.61275;-0.95546;-0.53035;,
 0.61275;1.28196;-0.53035;,
 -3.00815;2.13056;-0.53035;,
 -3.00815;-1.80406;-0.53035;,
 -4.18351;2.13056;-0.70957;,
 -4.18351;-1.80406;-0.70957;,
 0.61275;1.28196;0.62075;,
 -3.00815;2.13056;0.62075;,
 -4.18351;2.13056;0.25729;,
 0.61275;-0.95546;0.62075;,
 -3.00815;-1.80406;0.62075;,
 -4.18351;-1.80406;0.25729;,
 0.61275;-0.95546;-0.53035;,
 -3.00815;-1.80406;-0.53035;,
 -4.18351;-1.80406;-0.70957;,
 -4.18351;2.13056;0.25729;,
 -4.18351;-1.80406;0.25729;,
 0.61275;-0.95546;0.62075;,
 0.61275;1.28196;0.62075;,
 -3.67663;1.04630;-0.32751;,
 -3.47101;2.11959;-0.32751;,
 -5.06590;2.35027;-0.41143;,
 -5.24385;1.42141;-0.41143;,
 -6.89991;2.55744;-2.13995;,
 -7.02457;1.90676;-2.13995;,
 -3.47101;2.11959;0.73831;,
 -5.64870;2.43976;0.08309;,
 -7.31049;2.71848;-1.79773;,
 -3.67663;1.04630;0.73831;,
 -5.81847;1.55366;0.08309;,
 -7.46559;1.90886;-1.79773;,
 -3.67663;1.04630;-0.32751;,
 -5.24385;1.42141;-0.41143;,
 -7.02457;1.90676;-2.13995;,
 -7.31049;2.71848;-1.79773;,
 -7.46559;1.90886;-1.79773;,
 -3.67663;1.04630;0.73831;,
 -3.47101;2.11959;0.73831;,
 -4.15337;0.17228;-0.48613;,
 -4.08131;1.26269;-0.48613;,
 -5.69247;1.29548;-0.57005;,
 -5.75483;0.35180;-0.57005;,
 -7.53803;1.27554;-2.29857;,
 -7.58171;0.61446;-2.29857;,
 -4.08131;1.26269;0.57967;,
 -6.28185;1.31261;-0.07553;,
 -7.96529;1.38486;-1.95635;,
 -4.15337;0.17228;0.57967;,
 -6.34135;0.41237;-0.07553;,
 -8.01965;0.56232;-1.95635;,
 -4.15337;0.17228;-0.48613;,
 -5.75483;0.35180;-0.57005;,
 -7.58171;0.61446;-2.29857;,
 -7.96529;1.38486;-1.95635;,
 -8.01965;0.56232;-1.95635;,
 -4.15337;0.17228;0.57967;,
 -4.08131;1.26269;0.57967;,
 -0.81079;-0.12146;-0.67331;,
 0.49095;1.64176;-0.38499;,
 -1.38068;2.34094;-0.33411;,
 -2.04899;1.43571;-0.48213;,
 -3.15917;3.76830;-2.33599;,
 -3.62736;3.13416;-2.43969;,
 0.41193;1.44218;1.19223;,
 -1.99592;2.66286;0.27471;,
 -3.54209;4.10120;-1.89859;,
 -0.88983;-0.32102;0.90391;,
 -2.63348;1.79930;0.13349;,
 -4.12461;3.31216;-2.02761;,
 -0.81079;-0.12146;-0.67331;,
 -2.04899;1.43571;-0.48213;,
 -3.62736;3.13416;-2.43969;,
 -3.54209;4.10120;-1.89859;,
 -4.12461;3.31216;-2.02761;,
 -0.88983;-0.32102;0.90391;,
 0.41193;1.44218;1.19223;,
 -4.15337;-0.90542;-0.48613;,
 -4.08131;0.18499;-0.48613;,
 -5.69247;0.21780;-0.57005;,
 -5.75483;-0.72588;-0.57005;,
 -7.53803;0.19784;-2.29857;,
 -7.58171;-0.46324;-2.29857;,
 -4.08131;0.18499;0.57967;,
 -6.28185;0.23494;-0.07553;,
 -7.96529;0.30716;-1.95635;,
 -4.15337;-0.90542;0.57967;,
 -6.34135;-0.66532;-0.07553;,
 -8.01965;-0.51538;-1.95635;,
 -4.15337;-0.90542;-0.48613;,
 -5.75483;-0.72588;-0.57005;,
 -7.58171;-0.46324;-2.29857;,
 -7.96529;0.30716;-1.95635;,
 -8.01965;-0.51538;-1.95635;,
 -4.15337;-0.90542;0.57967;,
 -4.08131;0.18499;0.57967;,
 -3.87767;-1.82200;-0.48613;,
 -3.99707;-0.73574;-0.48613;,
 -5.58921;-0.98471;-0.57005;,
 -5.48589;-1.92479;-0.57005;,
 -7.40295;-1.32652;-2.29857;,
 -7.33057;-1.98506;-2.29857;,
 -3.99707;-0.73574;0.57967;,
 -6.17253;-1.07072;-0.07553;,
 -7.84275;-1.29346;-1.95635;,
 -3.87767;-1.82200;0.57967;,
 -6.07397;-1.96752;-0.07553;,
 -7.75269;-2.11286;-1.95635;,
 -3.87767;-1.82200;-0.48613;,
 -5.48589;-1.92479;-0.57005;,
 -7.33057;-1.98506;-2.29857;,
 -7.84275;-1.29346;-1.95635;,
 -7.75269;-2.11286;-1.95635;,
 -3.87767;-1.82200;0.57967;,
 -3.99707;-0.73574;0.57967;;
 
 60;
 4;3,2,1,0;,
 4;5,4,2,3;,
 4;2,7,6,1;,
 4;4,8,7,2;,
 4;7,10,9,6;,
 4;8,11,10,7;,
 4;10,13,12,9;,
 4;11,14,13,10;,
 4;16,15,4,5;,
 4;0,1,18,17;,
 4;22,21,20,19;,
 4;24,23,21,22;,
 4;21,26,25,20;,
 4;23,27,26,21;,
 4;26,29,28,25;,
 4;27,30,29,26;,
 4;29,32,31,28;,
 4;30,33,32,29;,
 4;35,34,23,24;,
 4;19,20,37,36;,
 4;41,40,39,38;,
 4;43,42,40,41;,
 4;40,45,44,39;,
 4;42,46,45,40;,
 4;45,48,47,44;,
 4;46,49,48,45;,
 4;48,51,50,47;,
 4;49,52,51,48;,
 4;54,53,42,43;,
 4;38,39,56,55;,
 4;60,59,58,57;,
 4;62,61,59,60;,
 4;59,64,63,58;,
 4;61,65,64,59;,
 4;64,67,66,63;,
 4;65,68,67,64;,
 4;67,70,69,66;,
 4;68,71,70,67;,
 4;73,72,61,62;,
 4;57,58,75,74;,
 4;79,78,77,76;,
 4;81,80,78,79;,
 4;78,83,82,77;,
 4;80,84,83,78;,
 4;83,86,85,82;,
 4;84,87,86,83;,
 4;86,89,88,85;,
 4;87,90,89,86;,
 4;92,91,80,81;,
 4;76,77,94,93;,
 4;98,97,96,95;,
 4;100,99,97,98;,
 4;97,102,101,96;,
 4;99,103,102,97;,
 4;102,105,104,101;,
 4;103,106,105,102;,
 4;105,108,107,104;,
 4;106,109,108,105;,
 4;111,110,99,100;,
 4;95,96,113,112;;
 
 MeshMaterialList {
  2;
  60;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  82;
  0.000000;0.000000;-1.000000;,
  0.075586;0.000000;-0.997139;,
  0.150739;0.000000;-0.988574;,
  0.228179;0.973619;0.000000;,
  0.114849;0.993383;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;1.000000;,
  -0.149392;0.000000;0.988778;,
  -0.295431;0.000000;0.955364;,
  0.051130;-0.009795;-0.998644;,
  0.385261;-0.073809;-0.919851;,
  0.672409;-0.128822;-0.728883;,
  0.145127;0.989409;-0.002806;,
  0.177185;0.983576;-0.034395;,
  0.208877;0.975718;-0.065913;,
  -0.280451;0.053729;0.958363;,
  -0.525843;0.100739;0.844595;,
  -0.731602;0.140157;0.667169;,
  0.051946;-0.003433;-0.998644;,
  0.391414;-0.025864;-0.919851;,
  0.683149;-0.045140;-0.728883;,
  0.022348;0.999746;-0.002810;,
  0.054880;0.997900;-0.034396;,
  0.087300;0.993999;-0.065910;,
  -0.284922;0.018830;0.958366;,
  -0.534237;0.035308;0.844597;,
  -0.743285;0.049124;0.667169;,
  0.026292;0.142385;-0.989462;,
  0.332551;-0.092043;-0.938583;,
  0.588482;-0.312540;-0.745659;,
  0.404361;0.912469;0.062394;,
  0.509838;0.857910;0.063684;,
  0.608124;0.791252;0.064075;,
  -0.318815;0.080952;0.944354;,
  -0.491486;0.225293;0.841240;,
  -0.634038;0.355827;0.686574;,
  0.051946;-0.003433;-0.998644;,
  0.391414;-0.025864;-0.919851;,
  0.683149;-0.045140;-0.728883;,
  0.022359;0.999746;-0.002809;,
  0.054884;0.997900;-0.034399;,
  0.087297;0.993999;-0.065919;,
  -0.284922;0.018830;0.958366;,
  -0.534237;0.035307;0.844597;,
  -0.743285;0.049123;0.667169;,
  0.051748;0.005687;-0.998644;,
  0.389920;0.042855;-0.919851;,
  0.680541;0.074796;-0.728883;,
  -0.152514;0.988297;-0.002805;,
  -0.120160;0.992158;-0.034394;,
  -0.087560;0.993976;-0.065911;,
  -0.283834;-0.031197;0.958366;,
  -0.532196;-0.058492;0.844598;,
  -0.740445;-0.081378;0.667172;,
  0.228180;-0.973619;-0.000000;,
  0.114850;-0.993383;-0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.230824;-0.972991;-0.002813;,
  -0.198877;-0.979420;-0.034405;,
  -0.166519;-0.983832;-0.065925;,
  -0.608521;0.116580;-0.784927;,
  0.982139;-0.188157;-0.000000;,
  -0.109409;-0.993993;-0.002807;,
  -0.076921;-0.996444;-0.034396;,
  -0.044274;-0.996843;-0.065914;,
  -0.618233;0.040852;-0.784932;,
  0.997824;-0.065941;-0.000000;,
  -0.742850;-0.641419;-0.191717;,
  -0.659470;-0.725912;-0.195323;,
  -0.566788;-0.800167;-0.196173;,
  -0.460856;0.463954;-0.756544;,
  0.806696;-0.589974;-0.034230;,
  -0.109411;-0.993993;-0.002821;,
  -0.076916;-0.996444;-0.034406;,
  -0.044263;-0.996843;-0.065920;,
  0.065781;-0.997830;-0.002811;,
  0.098205;-0.994571;-0.034401;,
  0.130426;-0.989264;-0.065920;,
  -0.615868;-0.067690;-0.784936;,
  0.994013;0.109260;0.000000;;
  60;
  4;1,1,0,0;,
  4;2,2,1,1;,
  4;4,4,3,3;,
  4;5,5,4,4;,
  4;7,7,6,6;,
  4;8,8,7,7;,
  4;55,55,54,54;,
  4;56,56,55,55;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;10,10,9,9;,
  4;11,11,10,10;,
  4;13,13,12,12;,
  4;14,14,13,13;,
  4;16,16,15,15;,
  4;17,17,16,16;,
  4;60,60,59,59;,
  4;61,61,60,60;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;19,19,18,18;,
  4;20,20,19,19;,
  4;22,22,21,21;,
  4;23,23,22,22;,
  4;25,25,24,24;,
  4;26,26,25,25;,
  4;65,65,64,64;,
  4;66,66,65,65;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;28,28,27,27;,
  4;29,29,28,28;,
  4;31,31,30,30;,
  4;32,32,31,31;,
  4;34,34,33,33;,
  4;35,35,34,34;,
  4;70,70,69,69;,
  4;71,71,70,70;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;37,37,36,36;,
  4;38,38,37,37;,
  4;40,40,39,39;,
  4;41,41,40,40;,
  4;43,43,42,42;,
  4;44,44,43,43;,
  4;75,75,74,74;,
  4;76,76,75,75;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;46,46,45,45;,
  4;47,47,46,46;,
  4;49,49,48,48;,
  4;50,50,49,49;,
  4;52,52,51,51;,
  4;53,53,52,52;,
  4;78,78,77,77;,
  4;79,79,78,78;,
  4;80,80,80,80;,
  4;81,81,81,81;;
 }
 MeshTextureCoords {
  114;
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;;
 }
}
