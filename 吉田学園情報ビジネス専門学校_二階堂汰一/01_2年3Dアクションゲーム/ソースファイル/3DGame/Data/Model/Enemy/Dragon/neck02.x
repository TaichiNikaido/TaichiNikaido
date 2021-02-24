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
 130;
 -6.07620;6.80131;-48.60264;,
 -7.30831;-0.84069;-48.20099;,
 0.61611;-0.86661;-48.03123;,
 0.57450;9.51755;-48.61350;,
 7.24673;6.87026;-48.32505;,
 8.54003;-0.75868;-47.87078;,
 11.08335;-0.72432;-47.81845;,
 9.38867;6.01866;-48.23117;,
 -11.22285;11.99219;-3.64033;,
 -12.71083;14.25209;-22.07731;,
 -0.01391;17.73789;-22.41468;,
 -0.38387;14.69518;-3.90291;,
 10.46215;12.10440;-3.18851;,
 12.69332;14.38355;-21.54799;,
 16.77406;13.30581;-21.27084;,
 13.94249;11.27201;-2.95972;,
 -9.05324;-0.34762;7.19582;,
 -9.08376;7.26963;6.76887;,
 -0.58192;9.85266;6.80489;,
 -0.54084;-0.38540;7.37619;,
 7.97083;-0.25953;7.55053;,
 7.94031;7.35773;7.12358;,
 10.67597;6.55492;7.22584;,
 10.70309;-0.22120;7.60713;,
 -10.10562;-12.75076;-20.72879;,
 -10.99613;-12.48110;-1.96291;,
 -0.26236;-17.94959;-1.62725;,
 0.13001;-18.16121;-20.40584;,
 10.31368;-12.64509;-20.30334;,
 10.41893;-12.37028;-1.51672;,
 13.85078;-10.57942;-1.48408;,
 13.58360;-10.87661;-20.27042;,
 16.43101;-0.80723;-21.03134;,
 17.36079;-1.21161;-2.18860;,
 -18.01905;-1.39469;-2.92577;,
 -16.30944;-0.97666;-21.71352;,
 -16.78820;13.13213;-21.97014;,
 -14.70091;11.12379;-3.55652;,
 -6.02342;-6.37094;-47.86437;,
 -10.32492;-9.65431;-36.03131;,
 0.45655;-13.09658;-37.33574;,
 0.64592;-8.30463;-47.61459;,
 0.33100;13.47375;-37.90912;,
 -9.68563;9.27662;-37.42724;,
 -12.90160;7.92856;-37.27357;,
 -13.83705;-0.78329;-36.73094;,
 -9.85182;-0.83265;-48.25466;,
 -8.21127;5.92758;-48.59788;,
 7.29951;-6.30199;-47.58678;,
 11.13813;-9.54324;-35.58411;,
 12.27774;-8.93323;-35.12808;,
 9.43547;-5.65618;-47.57755;,
 14.58440;-0.63621;-36.13875;,
 13.58229;8.06560;-36.72176;,
 10.36175;9.38036;-37.00953;,
 -0.26236;-17.94959;-1.62725;,
 -10.99613;-12.48110;-1.96291;,
 -9.02666;-6.98393;7.56844;,
 -0.50512;-9.30262;7.87648;,
 -11.78573;-0.33757;7.13855;,
 -11.81285;6.43855;6.75726;,
 7.99741;-6.89583;7.92318;,
 10.72677;-6.12537;7.93711;,
 -11.48878;-9.05621;-35.62327;,
 -8.16448;-5.74725;-47.94426;,
 -6.02342;-6.37094;-47.86437;,
 0.64592;-8.30463;-47.61459;,
 -14.44470;-10.72585;-2.07363;,
 -11.76205;-6.24174;7.46853;,
 -13.39219;-11.01620;-20.83248;,
 10.31368;-12.64509;-20.30334;,
 11.13813;-9.54324;-35.58411;,
 10.41893;-12.37028;-1.51672;,
 7.29951;-6.30199;-47.58678;,
 -10.10562;-12.75076;-20.72879;,
 -10.32492;-9.65431;-36.03131;,
 -0.72265;11.93317;-39.52325;,
 0.42694;11.60892;-42.05073;,
 0.34897;17.81186;-39.84895;,
 -0.77880;17.73104;-38.26862;,
 1.46684;11.94450;-39.47763;,
 1.41070;17.74237;-38.22300;,
 -0.88731;22.09084;-34.14344;,
 0.17615;24.11033;-33.11905;,
 0.12029;24.24844;-30.47230;,
 -0.92183;22.17503;-32.50756;,
 1.30219;22.10216;-34.09781;,
 1.26767;22.18636;-32.46194;,
 -0.91012;18.05522;-32.04638;,
 0.13609;18.33839;-29.76274;,
 0.14871;11.38986;-28.64309;,
 -0.89606;12.23498;-31.27558;,
 1.27938;18.06655;-32.00076;,
 1.29343;12.24632;-31.22995;,
 -1.03905;15.89088;-25.32114;,
 0.10953;15.83730;-27.86694;,
 0.01949;21.76940;-25.01917;,
 -1.10700;21.51863;-23.45766;,
 1.15045;15.90221;-25.27552;,
 1.08250;21.52996;-23.41204;,
 -1.22230;25.41604;-18.89180;,
 -0.16254;27.31600;-17.66035;,
 -0.21699;27.17317;-15.01151;,
 -1.25589;25.32533;-17.25718;,
 0.96720;25.42737;-18.84618;,
 0.93361;25.33666;-17.21156;,
 -1.23486;21.17893;-17.23652;,
 -0.18780;21.22158;-14.93425;,
 -0.15917;14.19302;-14.56280;,
 -1.20755;15.31015;-17.08972;,
 0.95464;21.19026;-17.19090;,
 0.98195;15.32149;-17.04410;,
 -1.34654;15.44956;-10.45339;,
 -0.20087;15.84255;-12.97086;,
 -0.30826;21.19548;-9.14612;,
 -1.43204;20.67402;-7.64777;,
 0.84295;15.46089;-10.40777;,
 0.75746;20.68535;-7.60215;,
 -1.55550;23.72911;-2.48110;,
 -0.50095;25.39260;-0.94089;,
 -0.55168;24.79525;1.64253;,
 -1.58681;23.35912;-0.88648;,
 0.63400;23.74044;-2.43550;,
 0.60269;23.37044;-0.84086;,
 -1.55125;19.27051;-1.57764;,
 -0.50155;18.91793;0.69595;,
 -0.44784;11.93347;-0.14688;,
 -1.50314;13.46277;-2.44407;,
 0.63824;19.28184;-1.53202;,
 0.68635;13.47410;-2.39845;;
 
 106;
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
 4;58,57,56,55;,
 4;60,37,34,59;,
 4;22,15,12,21;,
 4;22,23,33,15;,
 4;62,61,29,30;,
 4;10,42,43,9;,
 4;14,53,54,13;,
 4;53,14,32,52;,
 4;50,31,28,49;,
 4;40,27,24,39;,
 4;44,45,35,36;,
 4;64,63,45,46;,
 4;2,66,65,1;,
 4;6,51,48,5;,
 4;51,6,52,50;,
 4;52,32,31,50;,
 4;30,31,32,33;,
 4;62,30,33,23;,
 4;62,23,20,61;,
 4;58,19,16,57;,
 4;68,59,34,67;,
 4;34,35,69,67;,
 4;63,69,35,45;,
 4;40,71,70,27;,
 4;27,70,72,26;,
 4;58,55,29,61;,
 4;58,61,20,19;,
 4;19,20,21,18;,
 4;18,21,12,11;,
 4;11,12,13,10;,
 4;10,13,54,42;,
 4;3,42,54,4;,
 4;3,4,5,2;,
 4;2,5,48,66;,
 4;41,73,71,40;,
 4;63,75,74,69;,
 4;69,74,56,67;,
 4;68,67,56,57;,
 4;68,57,16,59;,
 4;59,16,17,60;,
 4;60,17,8,37;,
 4;37,8,9,36;,
 4;36,9,43,44;,
 4;47,44,43,0;,
 4;47,0,1,46;,
 4;46,1,65,64;,
 4;64,65,75,63;,
 4;79,78,77,76;,
 4;78,81,80,77;,
 4;85,84,83,82;,
 4;84,87,86,83;,
 4;91,90,89,88;,
 4;90,93,92,89;,
 4;81,92,93,80;,
 4;88,79,76,91;,
 4;82,83,78,79;,
 4;84,85,88,89;,
 4;85,82,79,88;,
 4;83,86,81,78;,
 4;86,87,92,81;,
 4;87,84,89,92;,
 4;97,96,95,94;,
 4;96,99,98,95;,
 4;103,102,101,100;,
 4;102,105,104,101;,
 4;109,108,107,106;,
 4;108,111,110,107;,
 4;99,110,111,98;,
 4;106,97,94,109;,
 4;100,101,96,97;,
 4;102,103,106,107;,
 4;103,100,97,106;,
 4;101,104,99,96;,
 4;104,105,110,99;,
 4;105,102,107,110;,
 4;115,114,113,112;,
 4;114,117,116,113;,
 4;121,120,119,118;,
 4;120,123,122,119;,
 4;127,126,125,124;,
 4;126,129,128,125;,
 4;117,128,129,116;,
 4;124,115,112,127;,
 4;118,119,114,115;,
 4;120,121,124,125;,
 4;121,118,115,124;,
 4;119,122,117,114;,
 4;122,123,128,117;,
 4;123,120,125,128;;
 
 MeshMaterialList {
  8;
  106;
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
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
  163;
  -0.731969;-0.626028;-0.268906;,
  0.011571;-0.947320;-0.320078;,
  0.748971;-0.618365;-0.238049;,
  -0.857508;0.394104;-0.330700;,
  0.001859;0.945997;-0.324170;,
  0.758014;0.564381;-0.326938;,
  -0.962494;0.130258;0.237986;,
  -0.011169;0.954158;0.299094;,
  0.222466;0.925938;0.305200;,
  -0.746176;-0.615676;0.253307;,
  -0.002121;-0.941957;0.335728;,
  0.741307;-0.607978;0.284299;,
  -0.692714;-0.626103;-0.357970;,
  0.013059;-0.916832;-0.399059;,
  0.021088;-0.055886;-0.998214;,
  -0.726726;0.571158;-0.381638;,
  0.713463;-0.618826;-0.328671;,
  0.021455;-0.055748;-0.998214;,
  -0.637846;0.574468;0.512971;,
  -0.021068;0.055742;0.998223;,
  -0.016937;-0.406042;0.913697;,
  -0.494135;-0.356617;0.792878;,
  -0.021192;0.055975;0.998207;,
  0.464345;-0.351656;0.812848;,
  -0.993173;0.070831;-0.092682;,
  -0.003561;0.997048;-0.076700;,
  0.286503;0.952349;-0.104629;,
  0.772622;-0.629976;-0.078645;,
  0.007596;-0.992994;-0.117924;,
  -0.762118;-0.637918;-0.110623;,
  -0.957590;-0.110853;-0.265958;,
  -0.932548;-0.089022;-0.349899;,
  0.021088;-0.055859;-0.998216;,
  0.021350;-0.055810;-0.998213;,
  0.968932;-0.100884;-0.225817;,
  0.991802;-0.110317;-0.064492;,
  0.963001;-0.044880;0.265736;,
  -0.021184;0.055905;0.998211;,
  -0.021078;0.055842;0.998217;,
  -0.887505;0.001763;0.460795;,
  -0.972718;-0.054897;0.225404;,
  -0.987061;-0.120557;-0.105724;,
  0.405891;-0.873602;-0.268461;,
  0.460294;-0.883780;-0.084042;,
  0.403277;-0.866526;0.294109;,
  0.303192;-0.776989;0.551691;,
  -0.021195;0.055874;0.998213;,
  -0.021156;0.055859;0.998215;,
  0.222908;0.927393;0.300422;,
  0.285927;0.954387;-0.085975;,
  0.348455;0.884783;-0.309417;,
  0.021216;-0.055817;-0.998216;,
  0.021163;-0.055835;-0.998216;,
  0.360875;-0.862435;-0.354930;,
  -0.385298;-0.877696;-0.284946;,
  -0.447227;-0.888476;-0.102951;,
  -0.406192;-0.870715;0.277243;,
  -0.195472;-0.417851;0.887238;,
  -0.020971;0.055874;0.998218;,
  -0.021001;0.055860;0.998218;,
  -0.244810;0.924973;0.290677;,
  -0.291956;0.951396;-0.098015;,
  -0.344399;0.881197;-0.323853;,
  0.020960;-0.055818;-0.998221;,
  0.021013;-0.055836;-0.998219;,
  -0.336838;-0.866045;-0.369468;,
  -0.960746;0.063744;-0.270007;,
  -0.856045;0.128305;-0.500725;,
  0.970448;0.073738;-0.229769;,
  -0.941546;0.172607;-0.289307;,
  -0.776990;0.335757;-0.532497;,
  0.950943;0.182401;-0.249875;,
  -0.980051;0.023435;0.197361;,
  -0.912486;0.050902;0.405930;,
  0.970685;0.033530;0.238006;,
  -0.980847;0.026162;0.193016;,
  -0.915754;0.056267;0.397778;,
  0.971633;0.036266;0.233698;,
  -0.907819;0.359670;-0.215644;,
  -0.796503;0.523971;-0.301723;,
  -0.940393;0.278389;0.195347;,
  -0.975401;0.183233;0.122549;,
  0.912244;0.369088;-0.177722;,
  0.967503;0.193287;0.163030;,
  -0.960991;0.090039;-0.261513;,
  -0.856388;0.179085;-0.484281;,
  0.970067;0.100032;-0.221277;,
  -0.942032;0.200391;-0.269109;,
  -0.777766;0.388915;-0.493787;,
  0.950300;0.210183;-0.229681;,
  -0.979993;0.000089;0.199030;,
  -0.912430;0.005348;0.409198;,
  0.970799;0.010184;0.239676;,
  -0.980790;0.003227;0.195039;,
  -0.915684;0.011476;0.401736;,
  0.971729;0.013331;0.235721;,
  -0.908653;0.378688;-0.175914;,
  -0.797642;0.551514;-0.244131;,
  -0.940883;0.254044;0.224054;,
  -0.975723;0.167050;0.141629;,
  0.911225;0.388105;-0.137996;,
  0.967197;0.177104;0.182112;,
  -0.961699;0.130022;-0.241307;,
  -0.857909;0.256333;-0.445293;,
  0.969519;0.140016;-0.201068;,
  -0.943143;0.240057;-0.229900;,
  -0.780073;0.464887;-0.418766;,
  0.949366;0.249851;-0.190468;,
  -0.979745;-0.037715;0.196666;,
  -0.911939;-0.068419;0.404582;,
  0.971041;-0.027620;0.237312;,
  -0.980558;-0.033989;0.193263;,
  -0.915225;-0.061205;0.398268;,
  0.971956;-0.023885;0.233946;,
  -0.910243;0.399860;-0.107562;,
  -0.799994;0.582205;-0.145072;,
  -0.941456;0.208402;0.265008;,
  -0.976114;0.136713;0.168853;,
  0.909748;0.409278;-0.069642;,
  0.966767;0.146767;0.209335;,
  0.995386;0.081122;-0.051248;,
  0.950347;0.140156;0.277842;,
  -0.369383;0.873464;-0.317203;,
  0.002208;0.940572;-0.339587;,
  0.947184;-0.079295;-0.310734;,
  0.736044;0.578728;-0.351160;,
  0.373219;0.877306;-0.301730;,
  -0.236109;0.869143;0.434561;,
  -0.013764;0.899244;0.437231;,
  0.208800;0.871446;0.443830;,
  0.609949;0.580925;0.538970;,
  0.867476;0.010845;0.497361;,
  0.021066;-0.055854;-0.998217;,
  0.021088;-0.055832;-0.998217;,
  0.021110;-0.055853;-0.998216;,
  0.021244;-0.055873;-0.998212;,
  -0.021235;0.055889;0.998211;,
  -0.020992;0.055906;0.998215;,
  -0.020987;0.055976;0.998212;,
  -0.244552;0.923522;0.295469;,
  -0.291733;0.949357;-0.116677;,
  -0.316298;0.877257;-0.361077;,
  0.020827;-0.055813;-0.998224;,
  0.020722;-0.055751;-0.998230;,
  0.020932;-0.055876;-0.998218;,
  0.874785;0.137262;-0.464662;,
  0.794981;0.343891;-0.499744;,
  0.802916;0.532248;-0.268398;,
  0.928510;0.288060;0.234287;,
  0.894210;0.060251;0.443574;,
  0.897760;0.065652;0.435565;,
  0.873918;0.188039;-0.448229;,
  0.793594;0.397046;-0.461046;,
  0.801370;0.559789;-0.210814;,
  0.928056;0.263716;0.262995;,
  0.894490;0.014698;0.446846;,
  0.897988;0.020862;0.439525;,
  0.873014;0.265290;-0.409227;,
  0.791987;0.473024;-0.386012;,
  0.799277;0.590482;-0.111751;,
  0.927394;0.218073;0.303947;,
  0.894954;-0.059069;0.442230;,
  0.898426;-0.051820;0.436056;;
  106;
  4;14,32,64,63;,
  4;17,33,52,51;,
  4;7,25,61,60;,
  4;8,26,49,48;,
  4;38,19,59,58;,
  4;37,22,47,46;,
  4;28,10,56,55;,
  4;27,11,44,43;,
  4;121,36,35,120;,
  4;6,24,41,40;,
  4;13,1,54,65;,
  4;123,122,62,4;,
  4;15,31,30,3;,
  4;16,2,42,53;,
  4;125,5,34,124;,
  4;125,126,50,5;,
  4;128,7,60,127;,
  4;20,57,56,10;,
  4;18,6,40,39;,
  4;130,8,48,129;,
  4;130,131,36,121;,
  4;23,45,44,11;,
  4;25,4,62,61;,
  4;26,5,50,49;,
  4;5,120,35,34;,
  4;2,27,43,42;,
  4;1,28,55,54;,
  4;3,30,41,24;,
  4;12,0,30,31;,
  4;32,133,132,64;,
  4;33,135,134,52;,
  4;16,124,34,2;,
  4;34,35,27,2;,
  4;11,27,35,36;,
  4;23,11,36,131;,
  4;23,37,46,136;,
  4;20,38,58,57;,
  4;21,39,40,9;,
  4;40,41,29,9;,
  4;0,29,41,30;,
  4;1,42,43,28;,
  4;28,43,44,10;,
  4;20,10,44,45;,
  4;20,136,46,38;,
  4;38,46,47,19;,
  4;128,129,48,7;,
  4;7,48,49,25;,
  4;25,49,50,4;,
  4;123,4,50,126;,
  4;14,51,52,32;,
  4;32,52,134,133;,
  4;13,53,42,1;,
  4;0,54,55,29;,
  4;29,55,56,9;,
  4;21,9,56,57;,
  4;21,57,58,137;,
  4;137,58,59,138;,
  4;18,127,60,139;,
  4;139,60,61,140;,
  4;140,61,62,141;,
  4;15,3,62,122;,
  4;143,63,64,142;,
  4;142,64,132,144;,
  4;12,65,54,0;,
  4;69,70,67,66;,
  4;146,71,68,145;,
  4;81,80,79,78;,
  4;148,83,82,147;,
  4;75,76,73,72;,
  4;150,77,74,149;,
  4;71,74,77,68;,
  4;72,69,66,75;,
  4;78,79,70,69;,
  4;80,81,72,73;,
  4;81,78,69,72;,
  4;147,82,71,146;,
  4;82,83,74,71;,
  4;83,148,149,74;,
  4;87,88,85,84;,
  4;152,89,86,151;,
  4;99,98,97,96;,
  4;154,101,100,153;,
  4;93,94,91,90;,
  4;156,95,92,155;,
  4;89,92,95,86;,
  4;90,87,84,93;,
  4;96,97,88,87;,
  4;98,99,90,91;,
  4;99,96,87,90;,
  4;153,100,89,152;,
  4;100,101,92,89;,
  4;101,154,155,92;,
  4;105,106,103,102;,
  4;158,107,104,157;,
  4;117,116,115,114;,
  4;160,119,118,159;,
  4;111,112,109,108;,
  4;162,113,110,161;,
  4;107,110,113,104;,
  4;108,105,102,111;,
  4;114,115,106,105;,
  4;116,117,108,109;,
  4;117,114,105,108;,
  4;159,118,107,158;,
  4;118,119,110,107;,
  4;119,160,161,110;;
 }
 MeshTextureCoords {
  130;
  0.400574;0.485930;,
  0.401581;0.501739;,
  0.400788;0.501793;,
  0.399592;0.480310;,
  0.399225;0.485787;,
  0.399976;0.501570;,
  0.399717;0.501498;,
  0.399109;0.487549;,
  0.494107;0.475191;,
  0.456273;0.470516;,
  0.453744;0.463305;,
  0.492001;0.469599;,
  0.491910;0.474959;,
  0.453699;0.470244;,
  0.453682;0.472473;,
  0.491880;0.476681;,
  0.516157;0.500719;,
  0.515280;0.484961;,
  0.514127;0.479617;,
  0.515300;0.500797;,
  0.514432;0.500537;,
  0.513555;0.484779;,
  0.513371;0.486439;,
  0.514154;0.500458;,
  0.551352;0.531724;,
  0.504645;0.531053;,
  0.504043;0.544659;,
  0.550771;0.545186;,
  0.456611;0.526160;,
  0.495366;0.525591;,
  0.494938;0.521886;,
  0.456207;0.522501;,
  0.454226;0.501670;,
  0.492978;0.502507;,
  0.496562;0.502885;,
  0.457543;0.502020;,
  0.457082;0.472833;,
  0.494782;0.476988;,
  0.618952;0.515851;,
  0.589419;0.524020;,
  0.592899;0.532585;,
  0.618476;0.520662;,
  0.421718;0.472126;,
  0.424158;0.480809;,
  0.424940;0.483598;,
  0.426194;0.501620;,
  0.401837;0.501723;,
  0.400892;0.487737;,
  0.400741;0.513037;,
  0.424957;0.519743;,
  0.425734;0.518481;,
  0.400452;0.511701;,
  0.423315;0.501316;,
  0.422256;0.483314;,
  0.422127;0.480594;,
  0.496680;0.537133;,
  0.497536;0.525820;,
  0.516922;0.514448;,
  0.516328;0.519245;,
  0.516433;0.500698;,
  0.515650;0.486680;,
  0.515197;0.514266;,
  0.514832;0.512672;,
  0.428141;0.518735;,
  0.402235;0.511890;,
  0.402090;0.513180;,
  0.401643;0.517180;,
  0.497805;0.522189;,
  0.517110;0.512913;,
  0.458940;0.522790;,
  0.550737;0.531461;,
  0.588773;0.523744;,
  0.504000;0.530778;,
  0.618551;0.515679;,
  0.458680;0.526378;,
  0.427131;0.519972;,
  0.598315;0.470310;,
  0.604628;0.471117;,
  0.599149;0.455684;,
  0.595193;0.455885;,
  0.598249;0.470282;,
  0.595127;0.455857;,
  0.584927;0.445037;,
  0.582402;0.440013;,
  0.575815;0.439669;,
  0.580856;0.444828;,
  0.584861;0.445009;,
  0.580791;0.444800;,
  0.579709;0.455078;,
  0.574051;0.454374;,
  0.571265;0.471662;,
  0.577792;0.469559;,
  0.579643;0.455050;,
  0.577726;0.469531;,
  0.562975;0.460463;,
  0.569333;0.460596;,
  0.562246;0.445837;,
  0.558337;0.446461;,
  0.562909;0.460435;,
  0.558271;0.446433;,
  0.546975;0.436764;,
  0.543934;0.432037;,
  0.537343;0.432393;,
  0.542907;0.436990;,
  0.546909;0.436736;,
  0.542841;0.436962;,
  0.542856;0.447306;,
  0.537151;0.447200;,
  0.536228;0.464687;,
  0.542492;0.461908;,
  0.542790;0.447278;,
  0.542426;0.461880;,
  0.525978;0.461561;,
  0.532266;0.460583;,
  0.522748;0.447265;,
  0.518996;0.448563;,
  0.525912;0.461533;,
  0.518930;0.448534;,
  0.506139;0.440961;,
  0.502330;0.436823;,
  0.495902;0.438309;,
  0.502171;0.441882;,
  0.506073;0.440933;,
  0.502105;0.441854;,
  0.503891;0.452055;,
  0.498258;0.452932;,
  0.500356;0.470309;,
  0.506048;0.466504;,
  0.503825;0.452026;,
  0.505982;0.466476;;
 }
}
