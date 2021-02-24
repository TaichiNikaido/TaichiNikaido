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
 165;
 2.67419;-5.59448;-5.50390;,
 4.28054;-12.24991;4.75231;,
 11.05535;-2.77721;9.82261;,
 8.96786;2.47179;-5.94019;,
 3.78443;-17.44200;25.12490;,
 10.58431;-7.36157;29.50823;,
 8.22881;2.91351;33.71691;,
 8.67171;6.89561;14.71966;,
 7.00502;8.01419;1.61783;,
 3.40607;-17.30684;45.29918;,
 10.26263;-7.26670;46.65686;,
 3.15547;-12.39220;64.01665;,
 10.06918;-2.87222;61.77854;,
 7.82623;6.84699;59.36932;,
 7.96222;2.96406;47.83901;,
 1.22971;10.25886;16.22794;,
 1.59367;11.62494;-1.45589;,
 0.79608;6.48223;34.99432;,
 -6.73154;3.23175;33.43253;,
 -6.28690;7.21288;14.43739;,
 -4.07544;8.24852;1.40891;,
 0.54794;6.51629;48.10818;,
 0.43051;10.22653;58.43911;,
 -7.13238;7.16422;59.08714;,
 -6.99641;3.28122;47.55697;,
 -8.89066;-2.35365;9.44504;,
 -5.99002;2.78680;-6.22416;,
 -9.35942;-6.93637;29.12957;,
 -2.83125;-17.30138;24.99949;,
 -2.33513;-12.10934;4.62689;,
 -0.06336;-5.53658;-5.55601;,
 -9.68161;-6.84423;46.28146;,
 -9.87678;-2.44853;61.40090;,
 -3.46021;-12.25175;63.89123;,
 -3.21196;-17.16788;45.17493;,
 -0.56097;-45.93439;-24.57875;,
 -2.83199;-52.50933;-14.39773;,
 0.43974;-55.78588;-15.98415;,
 0.88899;-46.76746;-29.73093;,
 -3.42212;-65.74322;1.84115;,
 -0.15802;-69.22153;0.48624;,
 3.19359;-65.88383;1.96663;,
 3.78372;-52.64987;-14.27230;,
 2.17669;-45.99216;-24.52661;,
 -4.26388;-67.11944;21.73929;,
 -0.58444;-70.59299;21.39852;,
 -4.04789;-58.59440;42.96914;,
 -0.82407;-61.88607;43.81892;,
 2.56780;-58.73500;43.09454;,
 3.22425;-67.27698;21.87996;,
 2.13635;101.72803;181.25836;,
 0.04181;101.62468;181.42688;,
 0.07660;103.41491;181.65271;,
 2.17238;103.25987;181.06736;,
 -2.03851;101.81635;181.18077;,
 -2.00186;103.34584;180.98783;,
 -1.95815;104.81468;180.39278;,
 0.12871;104.98078;180.62822;,
 2.21622;104.72851;180.47198;,
 1.38806;-6.36590;-10.70749;,
 1.62575;4.35945;-11.31999;,
 -1.19288;-57.48919;68.24913;,
 2.20726;-54.60750;66.72732;,
 -4.40844;-54.46687;66.60197;,
 -4.96402;-64.76675;84.08488;,
 -1.74218;-67.47472;86.07985;,
 1.66697;-64.90663;84.21061;,
 -9.95795;5.88580;75.00318;,
 -3.57074;-3.10454;79.88309;,
 -7.18688;14.68072;70.29520;,
 -7.12986;31.41239;85.78457;,
 -9.90393;23.55392;91.53022;,
 -3.51333;15.50214;97.44757;,
 0.38612;17.47256;68.85200;,
 7.77350;14.36241;70.57950;,
 7.84168;31.09406;86.06800;,
 0.44889;33.89108;83.99660;,
 9.98809;5.46206;75.38084;,
 3.04499;-3.24517;80.00845;,
 3.11767;15.36213;97.57323;,
 10.06145;23.13127;91.90906;,
 -2.39766;-88.49223;97.21985;,
 1.01930;-86.22200;95.51057;,
 -5.65172;-86.07953;95.38585;,
 -6.38457;-105.75609;110.94910;,
 -3.09916;-107.96947;112.34247;,
 0.33023;-105.89853;111.07590;,
 -9.69631;55.96809;115.42604;,
 -3.27250;48.79939;120.86932;,
 -6.94475;62.94118;110.15704;,
 -6.79908;92.54200;134.60006;,
 -9.52146;86.17617;138.54575;,
 -3.05098;79.61635;142.66482;,
 0.64841;65.12409;108.52933;,
 8.07117;62.62078;110.44091;,
 8.25860;92.22304;134.88367;,
 0.79961;94.52047;133.40936;,
 10.32448;55.54346;115.80454;,
 3.40086;48.65815;120.99310;,
 3.66365;79.47384;142.79157;,
 10.55653;85.74816;138.92567;,
 -3.40417;-113.84121;121.94950;,
 0.02085;-111.80773;121.18243;,
 -6.70902;-111.66577;121.05520;,
 -3.55485;-121.95198;120.80106;,
 -8.37863;-120.92248;122.16894;,
 -7.32817;-118.06136;128.43415;,
 -3.69346;-119.53762;130.71811;,
 1.25313;-121.12630;122.35329;,
 0.08916;-118.21747;128.57517;,
 -9.56291;97.23738;152.73474;,
 -3.06076;90.78196;155.35297;,
 -6.87047;103.49791;150.29202;,
 -5.05585;102.68987;156.85264;,
 -7.16682;98.30024;160.08167;,
 -5.30714;93.25034;159.59916;,
 0.72436;105.44235;149.60612;,
 8.20186;103.17661;150.57897;,
 6.10603;102.45157;157.06355;,
 0.53259;104.54802;158.79410;,
 10.53205;96.80918;153.11706;,
 3.66693;90.63847;155.48132;,
 5.85468;93.01205;159.81030;,
 7.90603;97.98194;160.36544;,
 4.12047;95.33731;170.27621;,
 0.08279;94.58832;171.35671;,
 5.25462;98.74490;170.49108;,
 -3.87305;95.50699;170.12609;,
 -4.87209;98.95851;170.29984;,
 -3.70121;102.02278;168.26855;,
 0.29947;103.11499;169.43443;,
 4.29250;101.85301;168.41875;,
 0.20738;91.73150;161.65134;,
 -0.06336;-5.53658;-5.55601;,
 -2.33513;-12.10934;4.62689;,
 -0.56097;-45.93439;-24.57875;,
 0.88899;-46.76746;-29.73093;,
 -2.83125;-17.30138;24.99949;,
 3.78443;-17.44200;25.12490;,
 4.28054;-12.24991;4.75231;,
 2.67419;-5.59448;-5.50390;,
 2.17669;-45.99216;-24.52661;,
 -3.21196;-17.16788;45.17493;,
 -3.46021;-12.25175;63.89123;,
 3.15547;-12.39220;64.01665;,
 3.40607;-17.30684;45.29918;,
 3.04499;-3.24517;80.00845;,
 -3.57074;-3.10454;79.88309;,
 -3.51333;15.50214;97.44757;,
 3.11767;15.36213;97.57323;,
 3.40086;48.65815;120.99310;,
 -3.27250;48.79939;120.86932;,
 -3.05098;79.61635;142.66482;,
 3.66365;79.47384;142.79157;,
 3.66693;90.63847;155.48132;,
 -3.06076;90.78196;155.35297;,
 -6.70902;-111.66577;121.05520;,
 -7.45143;-16.00268;150.29899;,
 -9.08654;-109.55453;128.85469;,
 -1.93690;-17.52147;152.35122;,
 3.71284;-16.23942;150.50906;,
 0.02085;-111.80773;121.18243;,
 2.18703;-109.79091;129.06707;,
 -3.54289;-111.42682;131.86669;,
 -3.40417;-113.84121;121.94950;;
 
 140;
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;7,6,5,2;,
 4;8,7,2,3;,
 4;5,10,9,4;,
 4;10,12,11,9;,
 4;14,13,12,10;,
 4;6,14,10,5;,
 4;16,15,7,8;,
 4;15,17,6,7;,
 4;19,18,17,15;,
 4;20,19,15,16;,
 4;17,21,14,6;,
 4;21,22,13,14;,
 4;24,23,22,21;,
 4;18,24,21,17;,
 4;26,25,19,20;,
 4;25,27,18,19;,
 4;29,28,27,25;,
 4;30,29,25,26;,
 4;27,31,24,18;,
 4;31,32,23,24;,
 4;34,33,32,31;,
 4;28,34,31,27;,
 4;38,37,36,35;,
 4;37,40,39,36;,
 4;42,41,40,37;,
 4;43,42,37,38;,
 4;40,45,44,39;,
 4;45,47,46,44;,
 4;49,48,47,45;,
 4;41,49,45,40;,
 4;53,52,51,50;,
 4;52,55,54,51;,
 4;57,56,55,52;,
 4;58,57,52,53;,
 4;26,60,59,30;,
 4;60,3,0,59;,
 4;16,8,3,60;,
 4;20,16,60,26;,
 4;62,61,47,48;,
 4;61,63,46,47;,
 4;65,64,63,61;,
 4;66,65,61,62;,
 4;68,67,32,33;,
 4;67,69,23,32;,
 4;71,70,69,67;,
 4;72,71,67,68;,
 4;69,73,22,23;,
 4;73,74,13,22;,
 4;76,75,74,73;,
 4;70,76,73,69;,
 4;74,77,12,13;,
 4;77,78,11,12;,
 4;80,79,78,77;,
 4;75,80,77,74;,
 4;82,81,65,66;,
 4;81,83,64,65;,
 4;85,84,83,81;,
 4;86,85,81,82;,
 4;88,87,71,72;,
 4;87,89,70,71;,
 4;91,90,89,87;,
 4;92,91,87,88;,
 4;89,93,76,70;,
 4;93,94,75,76;,
 4;96,95,94,93;,
 4;90,96,93,89;,
 4;94,97,80,75;,
 4;97,98,79,80;,
 4;100,99,98,97;,
 4;95,100,97,94;,
 4;102,101,85,86;,
 4;101,103,84,85;,
 4;107,106,105,104;,
 4;109,107,104,108;,
 4;111,110,91,92;,
 4;110,112,90,91;,
 4;114,113,112,110;,
 4;115,114,110,111;,
 4;112,116,96,90;,
 4;116,117,95,96;,
 4;119,118,117,116;,
 4;113,119,116,112;,
 4;117,120,100,95;,
 4;120,121,99,100;,
 4;123,122,121,120;,
 4;118,123,120,117;,
 4;50,51,125,124;,
 4;53,50,124,126;,
 4;51,54,127,125;,
 4;54,55,128,127;,
 4;55,56,129,128;,
 4;56,57,130,129;,
 4;57,58,131,130;,
 4;58,53,126,131;,
 4;125,127,115,132;,
 4;127,128,114,115;,
 4;128,129,113,114;,
 4;129,130,119,113;,
 4;130,131,118,119;,
 4;131,126,123,118;,
 4;126,124,122,123;,
 4;124,125,132,122;,
 4;35,36,134,133;,
 4;136,135,30,59;,
 4;36,39,137,134;,
 4;41,42,139,138;,
 4;42,43,140,139;,
 4;141,136,59,0;,
 4;39,44,142,137;,
 4;44,46,143,142;,
 4;48,49,145,144;,
 4;49,41,138,145;,
 4;62,48,144,146;,
 4;46,63,147,143;,
 4;63,64,148,147;,
 4;66,62,146,149;,
 4;82,66,149,150;,
 4;64,83,151,148;,
 4;83,84,152,151;,
 4;86,82,150,153;,
 4;102,86,153,154;,
 4;84,103,155,152;,
 3;156,115,111;,
 3;156,157,115;,
 3;156,158,157;,
 4;157,159,132,115;,
 4;159,160,122,132;,
 3;121,162,161;,
 3;121,160,162;,
 3;121,122,160;,
 4;159,157,158,163;,
 4;160,159,163,162;,
 4;104,105,156,164;,
 4;105,106,158,156;,
 4;106,107,163,158;,
 4;108,104,164,161;,
 4;107,109,162,163;,
 4;109,108,161,162;;
 
 MeshMaterialList {
  8;
  140;
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
  1,
  0,
  1,
  1,
  1,
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
  182;
  0.928990;-0.154155;-0.336472;,
  0.955556;-0.294353;-0.016433;,
  0.947543;-0.289637;0.135177;,
  0.722432;0.674757;-0.150979;,
  0.787680;0.611113;0.078114;,
  0.779500;0.563788;-0.272987;,
  -0.686929;0.704688;-0.177602;,
  -0.763413;0.644064;0.048806;,
  -0.743954;0.596121;-0.301948;,
  -0.921245;-0.114973;-0.371603;,
  -0.965878;-0.253551;-0.052841;,
  -0.963409;-0.249102;0.098953;,
  -0.959875;-0.175056;0.219079;,
  0.942631;-0.215424;0.255029;,
  -0.731854;0.442152;-0.518547;,
  0.769059;0.410254;-0.490142;,
  -0.943317;-0.227665;0.241499;,
  0.922997;-0.267316;0.276801;,
  -0.687382;0.534900;-0.491312;,
  0.727560;0.504856;-0.464518;,
  -0.857892;-0.491322;0.150417;,
  0.663966;-0.566884;0.487640;,
  -0.616083;0.769331;0.169031;,
  0.641258;0.742691;0.192867;,
  0.018559;0.990841;0.133755;,
  0.849617;-0.471399;0.236506;,
  -0.963748;-0.209032;0.165816;,
  0.947067;-0.249568;0.201938;,
  -0.742040;0.508541;-0.436764;,
  -0.988373;-0.092464;0.120704;,
  0.778984;0.476225;-0.407913;,
  0.028229;0.646688;-0.762232;,
  0.978300;-0.134199;0.157859;,
  -0.951889;-0.176393;0.250584;,
  0.933379;-0.216416;0.286300;,
  -0.710279;0.442201;-0.547688;,
  -0.984407;-0.113114;0.134713;,
  0.748615;0.411222;-0.520069;,
  0.028419;0.740039;-0.671963;,
  0.972910;-0.154737;0.171762;,
  -0.963812;-0.265463;0.024426;,
  0.979336;-0.200816;-0.023949;,
  -0.670404;0.733401;-0.112608;,
  0.704673;0.704238;-0.086519;,
  0.953351;-0.263700;-0.146914;,
  0.982916;-0.184048;-0.001420;,
  0.778706;0.623472;0.070000;,
  0.913010;0.075397;-0.400909;,
  0.950985;-0.303707;0.058222;,
  0.980206;-0.180482;0.081375;,
  0.783462;0.614634;-0.091720;,
  0.019305;0.994841;0.099597;,
  -0.753611;0.656043;0.040970;,
  0.025011;0.971259;-0.236708;,
  0.027474;0.892709;-0.449794;,
  -0.752638;0.647257;-0.120806;,
  -0.989077;-0.142220;-0.038736;,
  -0.957430;-0.223229;-0.183021;,
  -0.893159;0.113710;-0.435129;,
  -0.989358;-0.138688;0.043994;,
  -0.964534;-0.263042;0.021970;,
  -0.890315;-0.032125;-0.454212;,
  -0.025620;-0.962134;0.271371;,
  -0.946080;0.239434;0.218182;,
  0.982537;-0.141349;-0.121005;,
  0.981079;-0.189440;0.039962;,
  0.018685;0.991950;0.125241;,
  0.024139;0.985398;-0.168549;,
  -0.982367;-0.099662;-0.158183;,
  -0.989040;-0.147621;0.002653;,
  -0.758074;0.284463;-0.586860;,
  -0.989561;-0.115062;0.086775;,
  0.028472;0.756640;-0.653211;,
  0.979796;-0.156873;0.124059;,
  -0.986250;-0.088845;0.139343;,
  0.028096;0.627826;-0.777847;,
  0.975620;-0.130477;0.176468;,
  -0.785167;-0.535604;0.310871;,
  0.024964;0.973858;-0.225781;,
  0.991350;0.054182;0.119542;,
  -0.026549;-0.470340;0.882086;,
  0.530768;-0.396229;0.749192;,
  -0.013460;0.237091;0.971394;,
  0.192039;0.227533;0.954647;,
  -0.574948;-0.372562;0.728445;,
  -0.218363;0.236550;0.946764;,
  -0.205092;0.457563;0.865201;,
  -0.007286;0.462595;0.886540;,
  0.190808;0.449305;0.872764;,
  -0.027189;-0.906557;0.421207;,
  -0.546740;-0.750462;0.371326;,
  -0.975907;0.078043;0.203754;,
  -0.780873;0.608439;0.141559;,
  0.021666;0.999253;-0.032009;,
  0.517321;0.854449;0.047925;,
  0.969928;0.036805;0.240593;,
  0.500154;-0.772511;0.391246;,
  -0.958692;-0.055060;-0.279065;,
  -0.942104;-0.211847;-0.259925;,
  -0.793012;-0.457284;-0.402521;,
  -0.932949;-0.129013;-0.336097;,
  -0.936615;-0.315077;-0.153229;,
  -0.739737;-0.619199;-0.263405;,
  0.927588;-0.354539;-0.117822;,
  0.941479;-0.251658;-0.224243;,
  0.965383;-0.095798;-0.242609;,
  -0.931090;-0.362138;0.043905;,
  -0.710306;-0.696675;0.100548;,
  -0.927788;-0.360627;0.095696;,
  -0.703943;-0.684433;0.189778;,
  0.907350;-0.399617;0.130471;,
  0.912589;-0.401213;0.078796;,
  0.579477;-0.798803;-0.161615;,
  0.891006;-0.447359;-0.077318;,
  -0.905624;-0.409218;-0.111291;,
  -0.154024;-0.674471;-0.722056;,
  -0.000846;-0.685820;-0.727771;,
  0.152360;-0.680965;-0.716291;,
  0.004163;-0.545182;-0.838307;,
  -0.041865;-0.543622;-0.838285;,
  0.050183;-0.545586;-0.836551;,
  -0.209774;-0.725574;-0.655391;,
  -0.003311;-0.746073;-0.665856;,
  0.203300;-0.734373;-0.647584;,
  0.006500;-0.479446;-0.877547;,
  0.345013;-0.810342;-0.473616;,
  -0.360931;-0.795358;-0.486964;,
  -0.973962;0.059331;-0.218810;,
  -0.021864;-0.150163;0.988419;,
  0.370264;-0.146526;0.917298;,
  -0.978934;0.044680;-0.199230;,
  -0.022675;-0.190127;0.981497;,
  0.990595;-0.002768;-0.136796;,
  -0.281165;-0.904087;0.321827;,
  -0.026445;-0.940778;0.337990;,
  -0.466089;-0.588552;0.660582;,
  0.230034;-0.914917;0.331680;,
  0.415143;-0.607178;0.677489;,
  0.787770;-0.490565;-0.372511;,
  0.722469;-0.650039;-0.235559;,
  0.938752;-0.168640;-0.300508;,
  0.675891;-0.726011;0.126806;,
  0.666547;-0.713569;0.215718;,
  0.904862;-0.070232;-0.419872;,
  0.791146;0.251659;-0.557454;,
  -0.606339;-0.773610;-0.184068;,
  -0.911441;0.411262;0.011819;,
  -0.816788;-0.544763;0.189976;,
  0.701850;-0.548759;0.454169;,
  0.860780;0.455270;0.227568;,
  0.936750;-0.154446;0.314078;,
  0.969004;0.028556;0.245389;,
  -0.953629;-0.114409;0.278391;,
  -0.975476;0.070178;0.208617;,
  -0.958872;0.251998;0.130620;,
  -0.133362;0.974828;-0.178676;,
  0.023904;0.983741;-0.177997;,
  0.180577;0.968244;-0.172901;,
  0.963226;0.210437;0.167069;,
  -0.999577;0.021362;-0.019752;,
  0.999617;-0.021036;0.018010;,
  0.999623;-0.021001;0.017703;,
  -0.999567;0.021434;-0.020169;,
  -0.999575;0.021373;-0.019828;,
  0.999617;-0.021046;0.017970;,
  0.994882;-0.011440;-0.100391;,
  -0.975644;0.049288;-0.213752;,
  -0.853611;0.101927;-0.510841;,
  -0.365195;-0.071841;0.928155;,
  -0.020621;-0.084399;0.996219;,
  -0.410519;-0.129949;0.902545;,
  0.959582;0.013490;-0.281104;,
  0.887426;0.021802;-0.460435;,
  -0.494986;-0.157239;0.854555;,
  0.455081;-0.177334;0.872613;,
  -0.038969;-0.003590;-0.999234;,
  0.018941;-0.004890;-0.999809;,
  -0.996538;0.000561;-0.083131;,
  -0.535183;-0.126753;0.835173;,
  0.076787;-0.006173;-0.997028;,
  0.497066;-0.148524;0.854907;,
  0.998105;-0.041626;-0.045314;;
  140;
  4;47,64,44,0;,
  4;64,45,1,44;,
  4;46,4,45,64;,
  4;3,46,64,47;,
  4;45,65,48,1;,
  4;65,49,2,48;,
  4;50,5,49,65;,
  4;4,50,65,45;,
  4;53,66,46,3;,
  4;66,51,4,46;,
  4;52,7,51,66;,
  4;6,52,66,53;,
  4;51,67,50,4;,
  4;67,54,5,50;,
  4;55,8,54,67;,
  4;7,55,67,51;,
  4;58,68,52,6;,
  4;68,56,7,52;,
  4;57,10,56,68;,
  4;9,57,68,58;,
  4;56,69,55,7;,
  4;69,59,8,55;,
  4;60,11,59,69;,
  4;10,60,69,56;,
  4;100,99,98,97;,
  4;99,102,101,98;,
  4;104,103,139,138;,
  4;105,104,138,140;,
  4;102,107,106,101;,
  4;107,109,108,106;,
  4;111,110,142,141;,
  4;103,111,141,139;,
  4;83,82,80,81;,
  4;82,85,84,80;,
  4;87,86,85,82;,
  4;88,87,82,83;,
  4;58,70,61,9;,
  4;144,47,0,143;,
  4;53,3,47,144;,
  4;6,53,70,58;,
  4;113,112,142,110;,
  4;145,114,108,109;,
  4;116,115,114,145;,
  4;117,116,112,113;,
  4;26,71,59,11;,
  4;71,28,8,59;,
  4;29,14,28,71;,
  4;12,29,71,26;,
  4;28,72,54,8;,
  4;72,30,5,54;,
  4;31,15,30,72;,
  4;14,31,72,28;,
  4;30,73,49,5;,
  4;73,27,2,49;,
  4;32,13,27,73;,
  4;15,32,73,30;,
  4;119,118,116,117;,
  4;118,120,115,116;,
  4;122,121,120,118;,
  4;123,122,118,119;,
  4;33,74,29,12;,
  4;74,35,14,29;,
  4;36,18,35,74;,
  4;16,36,74,33;,
  4;35,75,31,14;,
  4;75,37,15,31;,
  4;38,19,37,75;,
  4;18,38,75,35;,
  4;37,76,32,15;,
  4;76,34,13,32;,
  4;39,17,34,76;,
  4;19,39,76,37;,
  4;125,124,122,123;,
  4;124,126,121,122;,
  4;134,135,133,134;,
  4;137,134,134,136;,
  4;40,77,36,16;,
  4;146,42,18,36;,
  4;63,22,42,146;,
  4;20,147,77,40;,
  4;42,78,38,18;,
  4;78,43,19,38;,
  4;24,23,43,78;,
  4;22,24,78,42;,
  4;43,79,39,19;,
  4;148,41,17,39;,
  4;25,21,41,79;,
  4;23,149,79,43;,
  4;81,80,89,96;,
  4;151,81,150,95;,
  4;80,84,90,89;,
  4;84,153,91,152;,
  4;153,154,92,91;,
  4;155,156,93,155;,
  4;156,157,94,93;,
  4;158,151,95,158;,
  4;89,90,20,62;,
  4;90,91,63,20;,
  4;91,92,22,63;,
  4;92,93,24,22;,
  4;93,94,23,24;,
  4;94,95,149,23;,
  4;95,96,21,25;,
  4;96,89,62,21;,
  4;97,98,57,9;,
  4;100,97,9,61;,
  4;98,101,10,57;,
  4;103,104,44,1;,
  4;104,105,0,44;,
  4;105,140,143,0;,
  4;101,106,60,10;,
  4;106,108,11,60;,
  4;110,111,48,2;,
  4;111,103,1,48;,
  4;113,110,2,27;,
  4;108,114,26,11;,
  4;114,159,12,26;,
  4;160,113,27,13;,
  4;161,160,13,34;,
  4;159,162,33,12;,
  4;162,163,16,33;,
  4;164,161,34,17;,
  4;165,164,17,41;,
  4;163,166,40,16;,
  3;166,167,40;,
  3;166,127,20;,
  3;166,130,127;,
  4;170,128,169,168;,
  4;128,129,21,169;,
  3;41,132,165;,
  3;41,171,132;,
  3;41,172,171;,
  4;128,170,173,131;,
  4;129,128,131,174;,
  4;176,175,175,124;,
  4;177,177,130,166;,
  4;135,178,131,173;,
  4;179,176,124,179;,
  4;180,137,174,131;,
  4;181,181,165,132;;
 }
 MeshTextureCoords {
  165;
  0.488256;0.511574;,
  0.509190;0.525342;,
  0.518676;0.505745;,
  0.486447;0.494886;,
  0.551305;0.536083;,
  0.559369;0.515229;,
  0.568395;0.493973;,
  0.529126;0.485735;,
  0.502328;0.483421;,
  0.592993;0.535804;,
  0.594806;0.515033;,
  0.631657;0.525636;,
  0.626041;0.505942;,
  0.621392;0.485835;,
  0.597577;0.493868;,
  0.533312;0.478777;,
  0.496765;0.475951;,
  0.572104;0.486590;,
  0.569967;0.493314;,
  0.530702;0.485078;,
  0.503496;0.482936;,
  0.599203;0.486519;,
  0.620540;0.478844;,
  0.622969;0.485179;,
  0.599154;0.493212;,
  0.520775;0.504869;,
  0.488019;0.494235;,
  0.561466;0.514350;,
  0.552001;0.535792;,
  0.509886;0.525051;,
  0.488543;0.511454;,
  0.596909;0.514159;,
  0.628140;0.505065;,
  0.632353;0.525346;,
  0.593692;0.535516;,
  0.561138;0.614286;,
  0.535759;0.630644;,
  0.539777;0.638797;,
  0.573988;0.616359;,
  0.495345;0.663571;,
  0.498787;0.672225;,
  0.495176;0.663921;,
  0.535591;0.630994;,
  0.561068;0.614430;,
  0.445822;0.666995;,
  0.446749;0.675637;,
  0.393008;0.645784;,
  0.390964;0.653974;,
  0.392840;0.646134;,
  0.445634;0.667387;,
  0.873759;0.289549;,
  0.874409;0.289763;,
  0.874870;0.286059;,
  0.873359;0.286380;,
  0.874201;0.289366;,
  0.873798;0.286202;,
  0.872563;0.283163;,
  0.872748;0.282820;,
  0.872124;0.283342;,
  0.477702;0.513170;,
  0.476404;0.490981;,
  0.330175;0.643034;,
  0.334035;0.635865;,
  0.334203;0.635515;,
  0.290695;0.661141;,
  0.285802;0.667879;,
  0.290526;0.661489;,
  0.656223;0.487824;,
  0.665372;0.506423;,
  0.646107;0.469629;,
  0.678064;0.435015;,
  0.690322;0.451273;,
  0.701612;0.467930;,
  0.642036;0.463853;,
  0.644535;0.470288;,
  0.676489;0.435674;,
  0.673281;0.429887;,
  0.654124;0.488700;,
  0.664676;0.506713;,
  0.700914;0.468219;,
  0.688223;0.452147;,
  0.258072;0.720171;,
  0.262399;0.714522;,
  0.262564;0.714168;,
  0.223828;0.763124;,
  0.220433;0.768631;,
  0.223658;0.763478;,
  0.739607;0.384215;,
  0.749913;0.399046;,
  0.728336;0.369790;,
  0.778758;0.308553;,
  0.787294;0.321722;,
  0.794861;0.335293;,
  0.723881;0.365274;,
  0.726755;0.370452;,
  0.777171;0.309212;,
  0.775205;0.304460;,
  0.737499;0.385094;,
  0.749205;0.399338;,
  0.794154;0.335588;,
  0.785181;0.322607;,
  0.196525;0.783240;,
  0.198507;0.778180;,
  0.198678;0.777827;,
  0.749813;0.752290;,
  0.753332;0.750160;,
  0.766110;0.744241;,
  0.770299;0.747295;,
  0.752322;0.750582;,
  0.765331;0.744564;,
  0.816582;0.298839;,
  0.821047;0.312194;,
  0.811153;0.285887;,
  0.824430;0.287559;,
  0.831398;0.296640;,
  0.830134;0.307087;,
  0.808641;0.281865;,
  0.809570;0.286552;,
  0.823254;0.288052;,
  0.827630;0.283715;,
  0.814471;0.299725;,
  0.820341;0.312491;,
  0.828959;0.307580;,
  0.829809;0.297299;,
  0.850808;0.302770;,
  0.853621;0.304319;,
  0.851088;0.295720;,
  0.851652;0.302419;,
  0.852155;0.295278;,
  0.847794;0.288939;,
  0.849622;0.286680;,
  0.846950;0.289290;,
  0.833574;0.310229;,
  0.513822;0.513775;,
  0.488438;0.530128;,
  0.449357;0.595027;,
  0.438515;0.596751;,
  0.437742;0.543046;,
  0.437573;0.543396;,
  0.488270;0.530478;,
  0.513751;0.513919;,
  0.449070;0.595147;,
  0.387538;0.542714;,
  0.340968;0.530483;,
  0.340800;0.530832;,
  0.387373;0.543060;,
  0.301011;0.508074;,
  0.301179;0.507724;,
  0.257481;0.461430;,
  0.257313;0.461779;,
  0.199052;0.378937;,
  0.199215;0.378586;,
  0.144994;0.301913;,
  0.144824;0.302267;,
  0.113253;0.274489;,
  0.113427;0.274132;,
  0.750793;0.731010;,
  0.811251;0.533106;,
  0.767232;0.726642;,
  0.814690;0.536248;,
  0.810073;0.533596;,
  0.750084;0.731304;,
  0.766043;0.727131;,
  0.772648;0.730516;,
  0.752161;0.735510;;
 }
}
