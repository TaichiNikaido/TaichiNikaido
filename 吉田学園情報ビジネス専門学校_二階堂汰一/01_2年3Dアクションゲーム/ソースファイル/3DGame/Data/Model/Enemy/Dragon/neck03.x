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
 122;
 -6.07200;7.45449;-43.63479;,
 -7.22100;0.45077;-43.24581;,
 0.00000;0.38772;-43.24435;,
 0.00000;9.89810;-43.76842;,
 6.07200;7.45449;-43.63479;,
 7.22100;0.45077;-43.24581;,
 9.58500;0.46814;-43.24792;,
 8.05800;6.65334;-43.59085;,
 -8.32200;10.82384;-1.51928;,
 -8.45400;11.50436;-19.72439;,
 0.00000;15.15299;-20.77959;,
 0.00000;13.94518;-3.94219;,
 8.32200;10.82384;-1.51928;,
 8.45400;11.50436;-19.72439;,
 11.22000;10.30979;-19.37945;,
 11.04600;9.80382;-0.72553;,
 -7.75800;0.87994;7.49445;,
 -7.75800;7.86629;7.10761;,
 0.00000;10.17861;6.98119;,
 0.00000;0.80501;7.50049;,
 7.75800;0.87994;7.49445;,
 7.75800;7.86629;7.10761;,
 10.29900;7.10810;7.15098;,
 10.29900;0.90278;7.49477;,
 -7.75200;-10.44794;-17.68269;,
 -9.75900;-9.07357;0.01539;,
 -0.00000;-13.08260;0.22050;,
 0.00000;-14.32264;-17.44732;,
 7.75200;-10.44794;-17.68269;,
 9.75900;-9.07357;0.01539;,
 12.95400;-7.76313;-0.05137;,
 10.29000;-9.17952;-17.75831;,
 14.30700;0.35346;-18.82732;,
 13.74300;2.37105;-0.53088;,
 -13.74300;2.37105;-0.53088;,
 -14.30700;0.35346;-18.82732;,
 -11.22000;10.30979;-19.37945;,
 -11.04600;9.80382;-0.72553;,
 -6.07200;-4.62656;-42.96464;,
 -7.25100;-7.81516;-33.61966;,
 0.00000;-10.81196;-33.45317;,
 0.00000;-6.42042;-42.86682;,
 0.00000;13.60870;-34.80639;,
 -6.66000;9.87777;-34.59896;,
 -8.84100;8.65597;-34.53213;,
 -12.33000;0.69302;-34.09080;,
 -9.58500;0.46814;-43.24792;,
 -8.05800;6.65334;-43.59085;,
 6.07200;-4.62656;-42.96464;,
 7.25100;-7.81516;-33.61966;,
 9.62400;-6.83461;-33.67568;,
 8.05800;-4.03711;-42.99776;,
 12.33000;0.69302;-34.09080;,
 8.84100;8.65597;-34.53213;,
 6.66000;9.87777;-34.59896;,
 -7.75800;-5.20749;7.83162;,
 -0.00000;-7.35898;7.95083;,
 -10.29900;0.90278;7.49477;,
 -10.29900;7.10810;7.15098;,
 12.95400;-7.76313;-0.05137;,
 9.75900;-9.07357;0.01539;,
 7.75800;-5.20749;7.83162;,
 10.29900;-4.50412;7.79339;,
 -9.58500;0.46814;-43.24792;,
 -12.33000;0.69302;-34.09080;,
 -9.62400;-6.83461;-33.67568;,
 -8.05800;-4.03711;-42.99776;,
 -6.07200;-4.62656;-42.96464;,
 0.00000;-6.42042;-42.86682;,
 6.07200;-4.62656;-42.96464;,
 8.05800;-4.03711;-42.99776;,
 12.33000;0.69302;-34.09080;,
 9.58500;0.46814;-43.24792;,
 12.78600;-3.25057;-18.42546;,
 -7.75800;-5.20749;7.83162;,
 -0.00000;-7.35898;7.95083;,
 -12.95400;-7.76313;-0.05137;,
 -10.29900;-4.50412;7.79339;,
 -12.95400;-7.76313;-0.05137;,
 -10.29000;-9.17952;-17.75831;,
 -12.78600;-3.25057;-18.42546;,
 7.75800;-5.20749;7.83162;,
 -9.75900;-9.07357;0.01539;,
 -8.05800;-4.03711;-42.99776;,
 12.78600;-3.25057;-18.42546;,
 -12.78600;-3.25057;-18.42546;,
 -1.09500;13.39122;-12.50039;,
 0.00000;13.66491;-15.05493;,
 0.00000;19.18017;-11.46642;,
 -1.09500;18.73351;-9.92481;,
 1.09500;13.39122;-12.50039;,
 1.09500;18.73351;-9.92481;,
 -1.09500;22.01141;-4.89579;,
 0.00000;23.73331;-3.45267;,
 0.00000;23.25123;-0.84314;,
 -1.09500;21.71154;-3.28555;,
 1.09500;22.01141;-4.89579;,
 1.09500;21.71154;-3.28555;,
 -1.09500;17.59516;-3.79815;,
 0.00000;17.33934;-1.53450;,
 0.00000;10.32374;-2.07033;,
 -1.09500;11.75661;-4.41087;,
 1.09500;17.59516;-3.79815;,
 1.09500;11.75661;-4.41087;,
 -0.88800;13.12574;-25.71153;,
 0.00000;13.34580;-27.78421;,
 0.00000;17.82065;-24.87568;,
 -0.88800;17.45493;-23.62642;,
 0.88800;13.12574;-25.71153;,
 0.88800;17.45493;-23.62642;,
 -0.88800;20.11144;-19.54726;,
 0.00000;21.51094;-18.37575;,
 0.00000;21.11814;-16.26175;,
 -0.88800;19.86903;-18.24311;,
 0.88800;20.11144;-19.54726;,
 0.88800;19.86903;-18.24311;,
 -0.88800;16.53329;-18.65772;,
 0.00000;16.32404;-16.82323;,
 0.00000;10.63859;-17.25613;,
 -0.88800;11.79856;-19.15338;,
 0.88800;16.53329;-18.65772;,
 0.88800;11.79856;-19.15338;;
 
 96;
 4;3,2,1,0;,
 4;7,6,5,4;,
 4;11,10,9,8;,
 4;15,14,13,12;,
 4;19,18,17,16;,
 4;23,22,21,20;,
 4;27,26,25,24;,
 4;31,30,29,28;,
 4;15,33,32,14;,
 4;37,36,35,34;,
 4;41,40,39,38;,
 4;3,0,43,42;,
 4;47,46,45,44;,
 4;51,50,49,48;,
 4;7,53,52,6;,
 4;7,4,54,53;,
 4;18,11,8,17;,
 4;56,55,25,26;,
 4;58,37,34,57;,
 4;22,15,12,21;,
 4;22,23,33,15;,
 4;62,61,60,59;,
 4;10,42,43,9;,
 4;14,53,54,13;,
 4;53,14,32,52;,
 4;50,31,28,49;,
 4;40,27,24,39;,
 4;44,45,35,36;,
 4;66,65,64,63;,
 4;2,68,67,1;,
 4;6,70,69,5;,
 4;51,72,71,50;,
 3;32,73,52;,
 4;59,73,32,33;,
 4;62,59,33,23;,
 4;62,23,20,61;,
 4;75,19,16,74;,
 4;77,57,34,76;,
 3;80,79,78;,
 4;65,79,80,64;,
 4;40,49,28,27;,
 4;27,28,29,26;,
 4;56,26,29,81;,
 4;75,61,20,19;,
 4;19,20,21,18;,
 4;18,21,12,11;,
 4;11,12,13,10;,
 4;10,13,54,42;,
 4;3,42,54,4;,
 4;3,4,5,2;,
 4;2,5,69,68;,
 4;41,48,49,40;,
 4;65,39,24,79;,
 4;79,24,25,78;,
 4;77,76,82,74;,
 4;77,74,16,57;,
 4;57,16,17,58;,
 4;58,17,8,37;,
 4;37,8,9,36;,
 4;36,9,43,44;,
 4;47,44,43,0;,
 4;47,0,1,46;,
 4;46,1,67,83;,
 4;66,38,39,65;,
 4;71,84,31,50;,
 3;31,84,30;,
 3;85,35,45;,
 4;34,35,85,76;,
 4;89,88,87,86;,
 4;88,91,90,87;,
 4;95,94,93,92;,
 4;94,97,96,93;,
 4;101,100,99,98;,
 4;100,103,102,99;,
 4;91,102,103,90;,
 4;98,89,86,101;,
 4;92,93,88,89;,
 4;94,95,98,99;,
 4;95,92,89,98;,
 4;93,96,91,88;,
 4;96,97,102,91;,
 4;97,94,99,102;,
 4;107,106,105,104;,
 4;106,109,108,105;,
 4;113,112,111,110;,
 4;112,115,114,111;,
 4;119,118,117,116;,
 4;118,121,120,117;,
 4;109,120,121,108;,
 4;116,107,104,119;,
 4;110,111,106,107;,
 4;112,113,116,117;,
 4;113,110,107,116;,
 4;111,114,109,106;,
 4;114,115,120,109;,
 4;115,112,117,120;;
 
 MeshMaterialList {
  8;
  96;
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1,
  1,
  1,
  0,
  0,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.241569;0.034510;0.034510;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data/Texture/Enemy/Dragon/Scale.png";
   }
  }
  Material {
   0.103529;0.047059;0.047059;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data/Texture/Enemy/Dragon/Scale.png";
   }
  }
  Material {
   0.762353;0.746667;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "dragoneye.png";
   }
  }
  Material {
   0.144314;0.119216;0.081569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.040000;0.008000;0.016000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.279216;0.072157;0.072157;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data/Texture/Enemy/Dragon/Scale.png";
   }
  }
  Material {
   0.288000;0.176000;0.176000;1.000000;;
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
  144;
  -0.695140;-0.680214;-0.232572;,
  0.000000;-0.955591;-0.294695;,
  0.695140;-0.680214;-0.232572;,
  -0.734882;0.644931;-0.209790;,
  0.000000;0.971747;-0.236027;,
  0.734882;0.644931;-0.209790;,
  -0.716879;0.669675;0.193958;,
  0.000000;0.980009;0.198954;,
  0.716879;0.669675;0.193958;,
  -0.814114;-0.552564;0.178580;,
  -0.000000;-0.949173;0.314755;,
  0.814114;-0.552564;0.178580;,
  -0.667161;-0.670483;-0.324575;,
  0.000000;-0.921717;-0.387863;,
  0.000000;-0.055214;-0.998475;,
  -0.729480;0.635064;-0.254073;,
  0.667161;-0.670483;-0.324575;,
  -0.000392;-0.055490;-0.998459;,
  -0.934276;0.183553;0.305674;,
  0.000000;0.055301;0.998470;,
  -0.000000;-0.838583;0.544774;,
  -0.928918;-0.017493;0.369873;,
  -0.000581;0.055301;0.998470;,
  0.293677;-0.832963;0.468963;,
  -0.735479;0.673584;-0.073179;,
  0.000000;0.999258;-0.038519;,
  0.735479;0.673584;-0.073179;,
  0.714777;-0.693056;-0.093638;,
  0.000000;-0.997329;-0.073036;,
  -0.714777;-0.693056;-0.093638;,
  -0.977991;-0.097171;-0.184638;,
  -0.966586;-0.014722;-0.255920;,
  0.000000;-0.055288;-0.998470;,
  -0.000372;-0.055382;-0.998465;,
  0.977991;-0.097171;-0.184638;,
  0.997796;0.006836;-0.065996;,
  0.981016;0.065269;0.182613;,
  -0.000507;0.055263;0.998472;,
  0.000000;0.055246;0.998473;,
  -0.936831;0.083496;0.339671;,
  -0.981016;0.065269;0.182613;,
  -0.997796;0.006836;-0.065996;,
  0.357472;-0.896914;-0.260305;,
  0.411728;-0.908782;-0.067784;,
  0.362477;-0.891402;0.272054;,
  0.288732;-0.818956;0.495927;,
  -0.000157;0.055254;0.998472;,
  -0.000175;0.055301;0.998470;,
  0.315213;0.930462;0.186765;,
  0.409550;0.910976;-0.048916;,
  0.435767;0.875981;-0.206794;,
  -0.000167;-0.055352;-0.998467;,
  -0.000102;-0.055335;-0.998468;,
  0.305773;-0.884997;-0.351118;,
  -0.357472;-0.896914;-0.260305;,
  -0.411728;-0.908782;-0.067784;,
  -0.362477;-0.891402;0.272054;,
  -0.288732;-0.818956;0.495927;,
  0.000157;0.055254;0.998472;,
  0.000175;0.055301;0.998470;,
  -0.315213;0.930462;0.186765;,
  -0.409550;0.910976;-0.048916;,
  -0.435767;0.875981;-0.206794;,
  0.000167;-0.055352;-0.998467;,
  0.000102;-0.055335;-0.998468;,
  -0.305773;-0.884997;-0.351118;,
  0.933250;-0.350371;-0.079275;,
  -0.933250;-0.350371;-0.079275;,
  -0.965778;0.125313;-0.227089;,
  -0.865455;0.242048;-0.438635;,
  0.965778;0.125313;-0.227089;,
  -0.946387;0.235691;-0.220908;,
  -0.785873;0.451187;-0.422887;,
  0.946387;0.235691;-0.220908;,
  -0.975604;-0.023165;0.218310;,
  -0.903603;-0.045201;0.425980;,
  0.975604;-0.023165;0.218310;,
  -0.976473;-0.019554;0.214753;,
  -0.906998;-0.038188;0.419401;,
  0.976473;-0.019554;0.214753;,
  -0.910084;0.400539;-0.106374;,
  -0.799553;0.580473;-0.154161;,
  -0.934627;0.225543;0.274958;,
  -0.971660;0.149917;0.182763;,
  0.910084;0.400539;-0.106374;,
  0.971660;0.149917;0.182763;,
  -0.965800;0.125179;-0.227068;,
  -0.865540;0.241795;-0.438606;,
  0.965800;0.125179;-0.227068;,
  -0.946523;0.235381;-0.220657;,
  -0.786422;0.450640;-0.422451;,
  0.946523;0.235381;-0.220657;,
  -0.975588;-0.023143;0.218385;,
  -0.903540;-0.045157;0.426117;,
  0.975588;-0.023143;0.218385;,
  -0.976448;-0.019511;0.214868;,
  -0.906902;-0.038103;0.419615;,
  0.976448;-0.019511;0.214868;,
  -0.910383;0.399942;-0.106062;,
  -0.800213;0.579678;-0.153727;,
  -0.934705;0.225181;0.274991;,
  -0.971692;0.149678;0.182787;,
  0.910383;0.399942;-0.106062;,
  0.971692;0.149678;0.182787;,
  -0.421163;0.864942;-0.272942;,
  0.000000;0.943342;-0.331822;,
  0.966586;-0.014722;-0.255920;,
  0.729480;0.635064;-0.254073;,
  0.421163;0.864942;-0.272942;,
  -0.256550;0.909615;0.326777;,
  0.000000;0.942874;0.333150;,
  0.256550;0.909615;0.326777;,
  0.254958;0.908285;0.331685;,
  0.936831;0.083496;0.339671;,
  0.934276;0.183553;0.305674;,
  0.000038;-0.055318;-0.998469;,
  0.000000;-0.055362;-0.998466;,
  -0.000038;-0.055318;-0.998469;,
  -0.000352;-0.055275;-0.998471;,
  0.928918;-0.017493;0.369873;,
  -0.000138;0.055208;0.998475;,
  -0.000433;0.055225;0.998474;,
  0.000138;0.055208;0.998475;,
  0.000000;0.055191;0.998476;,
  -0.293677;-0.832963;0.468963;,
  0.000507;0.055263;0.998472;,
  0.000433;0.055225;0.998474;,
  0.000581;0.055301;0.998470;,
  -0.254958;0.908285;0.331685;,
  0.000372;-0.055382;-0.998465;,
  0.000392;-0.055490;-0.998459;,
  0.000352;-0.055275;-0.998471;,
  0.865455;0.242048;-0.438635;,
  0.785873;0.451187;-0.422887;,
  0.799553;0.580473;-0.154161;,
  0.934627;0.225543;0.274958;,
  0.903603;-0.045201;0.425980;,
  0.906998;-0.038188;0.419401;,
  0.865540;0.241795;-0.438606;,
  0.786422;0.450640;-0.422451;,
  0.800213;0.579678;-0.153727;,
  0.934705;0.225181;0.274991;,
  0.903540;-0.045157;0.426117;,
  0.906902;-0.038103;0.419615;;
  96;
  4;14,32,64,63;,
  4;17,33,52,51;,
  4;7,25,61,60;,
  4;8,26,49,48;,
  4;38,19,59,58;,
  4;37,22,47,46;,
  4;28,10,56,55;,
  4;27,11,44,43;,
  4;8,36,35,26;,
  4;6,24,41,40;,
  4;13,1,54,65;,
  4;105,104,62,4;,
  4;15,31,30,3;,
  4;16,2,42,53;,
  4;107,5,34,106;,
  4;107,108,50,5;,
  4;110,7,60,109;,
  4;20,57,56,10;,
  4;18,6,40,39;,
  4;112,8,48,111;,
  4;114,113,36,8;,
  4;23,45,44,11;,
  4;25,4,62,61;,
  4;26,5,50,49;,
  4;5,26,35,34;,
  4;2,27,43,42;,
  4;1,28,55,54;,
  4;3,30,41,24;,
  4;12,0,30,31;,
  4;32,116,115,64;,
  4;33,118,117,52;,
  4;16,106,34,2;,
  3;35,66,34;,
  4;11,66,35,36;,
  4;119,11,36,113;,
  4;121,37,46,120;,
  4;123,38,58,122;,
  4;21,39,40,9;,
  3;67,29,9;,
  4;0,29,67,30;,
  4;1,42,43,28;,
  4;28,43,44,10;,
  4;20,10,44,45;,
  4;123,120,46,38;,
  4;38,46,47,19;,
  4;110,111,48,7;,
  4;7,48,49,25;,
  4;25,49,50,4;,
  4;105,4,50,108;,
  4;14,51,52,32;,
  4;32,52,117,116;,
  4;13,53,42,1;,
  4;0,54,55,29;,
  4;29,55,56,9;,
  4;124,9,56,57;,
  4;126,122,58,125;,
  4;125,58,59,127;,
  4;128,109,60,6;,
  4;6,60,61,24;,
  4;24,61,62,3;,
  4;15,3,62,104;,
  4;130,63,64,129;,
  4;129,64,115,131;,
  4;12,65,54,0;,
  4;34,66,27,2;,
  3;27,66,11;,
  3;67,41,30;,
  4;40,41,67,9;,
  4;71,72,69,68;,
  4;133,73,70,132;,
  4;83,82,81,80;,
  4;135,85,84,134;,
  4;77,78,75,74;,
  4;137,79,76,136;,
  4;73,76,79,70;,
  4;74,71,68,77;,
  4;80,81,72,71;,
  4;82,83,74,75;,
  4;83,80,71,74;,
  4;134,84,73,133;,
  4;84,85,76,73;,
  4;85,135,136,76;,
  4;89,90,87,86;,
  4;139,91,88,138;,
  4;101,100,99,98;,
  4;141,103,102,140;,
  4;95,96,93,92;,
  4;143,97,94,142;,
  4;91,94,97,88;,
  4;92,89,86,95;,
  4;98,99,90,89;,
  4;100,101,92,93;,
  4;101,98,89,92;,
  4;140,102,91,139;,
  4;102,103,94,91;,
  4;103,141,142,94;;
 }
 MeshTextureCoords {
  122;
  0.410826;0.484578;,
  0.411795;0.499067;,
  0.410756;0.499198;,
  0.409674;0.479523;,
  0.409074;0.484578;,
  0.409711;0.499067;,
  0.409365;0.499032;,
  0.408878;0.486236;,
  0.498066;0.477608;,
  0.460514;0.476200;,
  0.457117;0.468652;,
  0.491864;0.471151;,
  0.495664;0.477608;,
  0.458074;0.476200;,
  0.458387;0.478671;,
  0.496909;0.479718;,
  0.516586;0.498180;,
  0.515788;0.483727;,
  0.514407;0.478943;,
  0.515479;0.498335;,
  0.514347;0.498180;,
  0.513549;0.483727;,
  0.513271;0.485295;,
  0.513981;0.498132;,
  0.543825;0.525995;,
  0.499750;0.522575;,
  0.499451;0.532550;,
  0.543408;0.535635;,
  0.544162;0.525995;,
  0.500174;0.522575;,
  0.500409;0.519315;,
  0.544405;0.522839;,
  0.459081;0.499269;,
  0.496921;0.495095;,
  0.500888;0.495095;,
  0.463210;0.499269;,
  0.461625;0.478671;,
  0.500097;0.479718;,
  0.606761;0.511511;,
  0.583486;0.519444;,
  0.583229;0.526900;,
  0.606650;0.515974;,
  0.428169;0.471847;,
  0.429558;0.479565;,
  0.430011;0.482093;,
  0.431425;0.498566;,
  0.412131;0.499032;,
  0.411203;0.486236;,
  0.607025;0.511511;,
  0.583801;0.519444;,
  0.583992;0.517005;,
  0.607150;0.510044;,
  0.427867;0.498566;,
  0.427459;0.482093;,
  0.427636;0.479565;,
  0.480347;0.512956;,
  0.480219;0.518309;,
  0.516953;0.498132;,
  0.516244;0.485295;,
  0.498025;0.516060;,
  0.498623;0.518771;,
  0.515043;0.510773;,
  0.514597;0.509318;,
  0.607390;0.498835;,
  0.584548;0.498276;,
  0.583574;0.517005;,
  0.606800;0.510044;,
  0.412209;0.509571;,
  0.411535;0.513282;,
  0.410457;0.509571;,
  0.410102;0.508352;,
  0.585083;0.498276;,
  0.607806;0.498835;,
  0.460130;0.506725;,
  0.517282;0.510773;,
  0.516408;0.515224;,
  0.501763;0.516060;,
  0.517570;0.509318;,
  0.499847;0.519315;,
  0.543958;0.522839;,
  0.545564;0.508088;,
  0.480684;0.512956;,
  0.501440;0.518771;,
  0.412427;0.508352;,
  0.546119;0.508088;,
  0.463820;0.506725;,
  0.531076;0.466682;,
  0.537456;0.466001;,
  0.528528;0.452279;,
  0.524668;0.453391;,
  0.531124;0.466682;,
  0.524716;0.453391;,
  0.512157;0.445235;,
  0.508590;0.440951;,
  0.502098;0.442150;,
  0.508150;0.445981;,
  0.512204;0.445235;,
  0.508198;0.445981;,
  0.509426;0.456223;,
  0.503818;0.456859;,
  0.505151;0.474314;,
  0.510950;0.470749;,
  0.509473;0.456223;,
  0.510998;0.470749;,
  0.563949;0.467343;,
  0.569125;0.466795;,
  0.561889;0.455662;,
  0.558762;0.456572;,
  0.563988;0.467343;,
  0.558800;0.456572;,
  0.548613;0.449962;,
  0.545718;0.446480;,
  0.540458;0.447458;,
  0.545368;0.450565;,
  0.548651;0.449962;,
  0.545407;0.450565;,
  0.546400;0.458865;,
  0.541855;0.459385;,
  0.542932;0.473531;,
  0.547633;0.470645;,
  0.546438;0.458865;,
  0.547671;0.470645;;
 }
}
