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
 284;
 -1.93092;-0.46628;-2.34306;,
 0.00000;-0.68618;-3.70100;,
 0.00000;0.43320;-4.03756;,
 -1.92018;0.59024;-3.01746;,
 1.93092;-0.46628;-2.34306;,
 1.92018;0.59024;-3.01746;,
 1.89742;0.83932;-2.73554;,
 0.00000;0.76208;-3.72700;,
 -1.89742;0.83932;-2.73554;,
 -1.55468;0.94834;-2.23498;,
 0.00000;0.87112;-3.02822;,
 0.00000;0.84920;-0.70840;,
 -1.98310;1.33824;-0.46340;,
 1.55468;0.94834;-2.23498;,
 1.98310;1.33824;-0.46340;,
 0.00000;3.36552;0.92598;,
 3.42638;4.25272;0.14490;,
 3.61700;4.68284;0.84936;,
 0.00000;3.96516;1.63098;,
 -3.42638;4.25272;0.14490;,
 -3.61700;4.68284;0.84936;,
 -3.23606;1.96392;1.18012;,
 0.00000;1.99798;1.79142;,
 0.00000;1.23510;1.48420;,
 -2.83334;1.16244;0.81792;,
 3.23606;1.96392;1.18012;,
 2.83334;1.16244;0.81792;,
 2.03896;0.39484;0.79306;,
 0.00000;0.22246;1.09036;,
 -2.03896;0.39484;0.79306;,
 0.00000;0.45466;-0.24916;,
 -2.17616;-0.10278;-0.24916;,
 2.17616;-0.10278;-0.24916;,
 1.93092;-0.46628;-2.34306;,
 0.00000;-0.68618;-3.70100;,
 -1.93092;-0.46628;-2.34306;,
 2.17616;-0.10278;-0.24916;,
 2.42788;0.95638;-0.24916;,
 2.03896;0.39484;0.79306;,
 2.83334;1.16244;0.81792;,
 3.23606;1.96392;1.18012;,
 2.63042;1.50884;-0.28608;,
 -2.03896;0.39484;0.79306;,
 -2.17616;-0.10278;-0.24916;,
 -2.42788;0.95638;-0.24916;,
 -2.83334;1.16244;0.81792;,
 -2.63042;1.50884;-0.28608;,
 -3.23606;1.96392;1.18012;,
 0.00000;2.72224;0.72612;,
 3.19306;2.91210;0.19068;,
 3.81338;3.83110;0.85376;,
 0.00000;3.09164;1.70222;,
 -3.19306;2.91210;0.19068;,
 -3.81338;3.83110;0.85376;,
 -1.95558;1.51374;-2.80010;,
 0.00000;1.44202;-3.88348;,
 0.00000;1.55104;-3.03440;,
 -1.80828;1.62276;-2.29954;,
 0.00000;1.06744;0.23504;,
 -2.63042;1.50884;-0.28608;,
 -2.79664;1.97594;-0.38618;,
 -2.45962;1.99256;-0.38516;,
 1.95558;1.51374;-2.80010;,
 1.80828;1.62276;-2.29954;,
 2.79664;1.97594;-0.38618;,
 2.45962;1.99256;-0.38516;,
 2.63042;1.50884;-0.28608;,
 0.51140;4.97224;-3.97042;,
 0.61786;3.83706;-3.97042;,
 0.93716;4.16796;-3.97042;,
 0.74434;4.51224;-3.97042;,
 0.00000;5.39970;-3.97042;,
 0.00000;4.34346;-3.97042;,
 -0.51140;4.97224;-3.97042;,
 -0.61786;3.83706;-3.97042;,
 -0.74434;4.51224;-3.97042;,
 -0.93718;4.16796;-3.97042;,
 -0.52424;5.02506;-4.16454;,
 -0.30704;5.31428;-4.26772;,
 0.00000;5.63160;-4.53246;,
 0.30844;5.31308;-4.26754;,
 0.52432;5.02498;-4.16536;,
 0.76500;4.64032;-4.14636;,
 0.52432;5.02498;-4.16536;,
 0.76500;4.64032;-4.14636;,
 0.74434;4.51224;-3.97042;,
 0.93716;4.16796;-3.97042;,
 0.95412;4.37754;-4.28792;,
 0.95412;4.37754;-4.28792;,
 0.61786;3.87686;-4.42954;,
 0.00000;4.38330;-4.44568;,
 0.00000;4.38330;-4.44568;,
 -0.61786;3.87686;-4.42954;,
 -0.95412;4.37754;-4.28792;,
 -0.95412;4.37754;-4.28792;,
 -0.93718;4.16796;-3.97042;,
 -0.74434;4.51224;-3.97042;,
 -0.76500;4.64032;-4.14636;,
 -0.76500;4.64032;-4.14636;,
 -0.52424;5.02506;-4.16454;,
 0.00396;6.08602;-2.96772;,
 0.80238;5.55918;-2.98472;,
 2.38354;6.68788;-2.18472;,
 0.00298;7.49124;-3.36706;,
 0.00298;7.49124;-3.36706;,
 1.82002;8.07646;-2.60658;,
 3.71326;6.44006;-2.29996;,
 3.66834;6.51302;-1.49050;,
 3.28606;6.03446;-1.74742;,
 3.31654;5.96426;-2.47368;,
 2.14694;5.20518;-2.52020;,
 2.24168;5.35462;-3.03750;,
 0.80238;5.55918;-2.98472;,
 0.90948;5.52356;-3.48340;,
 0.00298;7.49124;-3.36706;,
 1.04994;7.56276;-4.02498;,
 0.67666;6.22332;-4.16062;,
 0.00396;6.08602;-2.96772;,
 1.95844;8.04904;-3.25186;,
 1.04994;7.56276;-4.02498;,
 0.00298;7.49124;-3.36706;,
 1.82002;8.07646;-2.60658;,
 2.97962;7.89732;-2.41602;,
 3.28338;7.97500;-2.80394;,
 3.60848;7.03980;-1.86298;,
 3.75966;7.28968;-2.52038;,
 3.77730;6.79484;-2.40810;,
 3.71326;6.44006;-2.29996;,
 0.00000;5.63160;-4.53246;,
 0.30844;5.31308;-4.26754;,
 0.67666;6.22332;-4.16062;,
 0.00000;7.05724;-4.42456;,
 0.52432;5.02498;-4.16536;,
 0.90948;5.52356;-3.48340;,
 4.93078;6.92648;-1.10348;,
 3.77730;6.79484;-2.40810;,
 3.71326;6.44006;-2.29996;,
 2.90058;4.37840;-2.84446;,
 3.31654;5.96426;-2.47368;,
 2.24168;5.35462;-3.03750;,
 0.90948;5.52356;-3.48340;,
 0.52432;5.02498;-4.16536;,
 0.76500;4.64032;-4.14636;,
 -3.00174;2.72982;-0.75938;,
 -4.63604;4.90546;2.45752;,
 -4.28542;3.07922;2.01422;,
 -2.94550;1.38974;2.91566;,
 -4.28542;3.07922;2.01422;,
 -3.91354;3.34170;3.33742;,
 -2.81802;2.36772;3.72652;,
 0.00000;0.57996;4.65198;,
 0.00000;2.33512;4.87972;,
 -3.56216;4.50016;5.48972;,
 0.00000;3.19533;6.67548;,
 0.00000;2.06782;5.02224;,
 4.28542;3.07922;2.01422;,
 2.94550;1.38974;2.91566;,
 2.81802;2.36772;3.72652;,
 3.91354;3.34170;3.33742;,
 3.56216;4.50016;5.48972;,
 -1.73214;3.02306;-3.88864;,
 -2.33682;2.04706;-2.42334;,
 -1.36808;2.47398;-4.24306;,
 0.00000;2.47184;-4.91798;,
 0.00000;3.29098;-4.90240;,
 1.73214;3.02306;-3.88864;,
 1.36808;2.47398;-4.24304;,
 2.33682;2.04706;-2.42334;,
 -2.92068;1.86368;-0.99936;,
 -3.00174;2.72982;-0.75938;,
 -1.21508;2.36808;-3.09598;,
 -2.35670;1.90346;-0.62836;,
 -1.95964;2.42574;-0.31610;,
 2.92068;1.86368;-0.99936;,
 3.00174;2.72982;-0.75938;,
 2.35670;1.90346;-0.62836;,
 1.95964;2.42574;-0.31610;,
 1.21508;2.36808;-3.09598;,
 0.00000;2.26794;2.35166;,
 0.00000;2.35188;-3.85968;,
 -2.90058;4.37840;-2.84446;,
 -4.93078;6.92648;-1.10348;,
 -4.69458;5.21598;-0.79908;,
 -5.73402;6.46522;2.38530;,
 -4.52672;6.46940;5.94808;,
 -3.56216;4.50016;5.48972;,
 -4.52672;6.46940;5.94808;,
 0.00000;5.89868;8.29098;,
 5.73402;6.46522;2.38530;,
 4.63604;4.90546;2.45752;,
 3.56216;4.50016;5.48972;,
 4.52672;6.46940;5.94808;,
 4.69458;5.21598;-0.79908;,
 -0.76500;4.64032;-4.14636;,
 -0.52424;5.02506;-4.16454;,
 -0.90394;5.52254;-3.48538;,
 -2.23748;5.35430;-3.03904;,
 -3.31548;5.96506;-2.47414;,
 -3.71324;6.44122;-2.30008;,
 -3.77714;6.79482;-2.40816;,
 0.76500;4.64032;-4.14636;,
 0.95412;4.37754;-4.28792;,
 1.73214;3.02306;-3.88864;,
 0.95412;4.37754;-4.28792;,
 0.61786;3.87686;-4.42954;,
 0.00000;3.29098;-4.90240;,
 -0.95412;4.37754;-4.28792;,
 -0.76500;4.64032;-4.14636;,
 -1.73214;3.02306;-3.88864;,
 -0.95412;4.37754;-4.28792;,
 -0.61786;3.87686;-4.42954;,
 -4.91014;10.53498;2.45752;,
 -4.03346;9.59546;5.40072;,
 -4.14698;9.63116;-1.58732;,
 4.91014;10.53498;2.45752;,
 4.14698;9.63116;-1.58732;,
 4.03346;9.59546;5.40072;,
 4.28542;3.07922;2.01422;,
 3.91354;3.34170;3.33742;,
 3.00174;2.72982;-0.75938;,
 0.00000;10.65960;7.34840;,
 4.03346;9.59546;5.40072;,
 4.52672;6.46940;5.94808;,
 -4.03346;9.59546;5.40072;,
 -4.91014;10.53498;2.45752;,
 0.00000;12.79346;2.45752;,
 4.91014;10.53498;2.45752;,
 0.00000;11.14626;-2.88672;,
 -1.04452;7.56202;-4.02756;,
 -0.67062;6.22442;-4.16294;,
 1.04994;7.56276;-4.02498;,
 -0.30704;5.31428;-4.26772;,
 -0.52424;5.02506;-4.16454;,
 -0.90394;5.52254;-3.48538;,
 0.00298;7.49124;-3.36706;,
 -1.04452;7.56202;-4.02756;,
 -1.95562;8.04920;-3.25304;,
 -1.81668;8.07644;-2.60660;,
 0.00298;7.49124;-3.36706;,
 0.00396;6.08602;-2.96772;,
 -0.67062;6.22442;-4.16294;,
 -1.04452;7.56202;-4.02756;,
 0.00298;7.49124;-3.36706;,
 -2.38020;6.68786;-2.18474;,
 -0.72082;5.55814;-2.98618;,
 0.00396;6.08602;-2.96772;,
 0.00298;7.49124;-3.36706;,
 -1.81668;8.07644;-2.60660;,
 -3.28320;7.97610;-2.80372;,
 -2.97894;7.89824;-2.41470;,
 -0.90394;5.52254;-3.48538;,
 -0.72082;5.55814;-2.98618;,
 -2.14234;5.20472;-2.52084;,
 -2.23748;5.35430;-3.03904;,
 -3.76056;7.29118;-2.51958;,
 -3.60890;7.04112;-1.86112;,
 -3.31548;5.96506;-2.47414;,
 -3.28442;6.03502;-1.74660;,
 -3.66768;6.51394;-1.48918;,
 -3.71324;6.44122;-2.30008;,
 -3.77714;6.79482;-2.40816;,
 3.28606;6.03446;-1.74742;,
 3.66834;6.51302;-1.49050;,
 2.14694;5.20518;-2.52020;,
 2.97962;7.89732;-2.41602;,
 3.60848;7.03980;-1.86298;,
 -3.91354;3.34170;3.33742;,
 -2.14234;5.20472;-2.52084;,
 -2.97894;7.89824;-2.41470;,
 -3.28442;6.03502;-1.74660;,
 -3.60890;7.04112;-1.86112;,
 -3.66768;6.51394;-1.48918;,
 1.95844;8.04904;-3.25186;,
 0.00000;8.42086;-4.40136;,
 -1.95562;8.04920;-3.25304;,
 -3.28320;7.97610;-2.80372;,
 -3.76056;7.29118;-2.51958;,
 -3.77714;6.79482;-2.40816;,
 3.77730;6.79484;-2.40810;,
 3.28338;7.97500;-2.80394;,
 3.75966;7.28968;-2.52038;,
 0.90948;5.52356;-3.48340;,
 -0.90394;5.52254;-3.48538;,
 0.00000;4.38330;-4.44568;;
 
 210;
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;7,6,5,2;,
 4;8,7,2,3;,
 4;12,11,10,9;,
 4;11,14,13,10;,
 4;18,17,16,15;,
 4;20,18,15,19;,
 4;24,23,22,21;,
 4;23,26,25,22;,
 4;28,27,26,23;,
 4;29,28,23,24;,
 4;31,30,28,29;,
 4;30,32,27,28;,
 4;34,33,32,30;,
 4;35,34,30,31;,
 4;5,37,36,4;,
 4;37,39,38,36;,
 4;41,40,39,37;,
 4;6,41,37,5;,
 4;45,44,43,42;,
 4;44,3,0,43;,
 4;46,8,3,44;,
 4;47,46,44,45;,
 4;15,16,49,48;,
 4;16,17,50,49;,
 4;17,18,51,50;,
 4;19,15,48,52;,
 4;18,20,53,51;,
 4;20,19,52,53;,
 4;57,56,55,54;,
 4;11,12,59,58;,
 4;61,57,54,60;,
 4;56,63,62,55;,
 4;63,65,64,62;,
 4;14,11,58,66;,
 4;54,55,7,8;,
 4;56,57,9,10;,
 4;60,54,8,59;,
 4;57,61,12,9;,
 4;61,60,59,12;,
 4;55,62,6,7;,
 4;63,56,10,13;,
 4;62,64,66,6;,
 4;64,65,14,66;,
 4;65,63,13,14;,
 4;49,50,25,66;,
 4;50,51,22,25;,
 4;51,53,21,22;,
 4;53,52,59,21;,
 4;52,48,58,59;,
 4;48,49,66,58;,
 4;70,69,68,67;,
 4;68,72,71,67;,
 4;71,72,74,73;,
 4;74,76,75,73;,
 3;77,71,73;,
 3;78,71,77;,
 3;78,79,71;,
 3;80,71,79;,
 3;80,67,71;,
 3;80,81,67;,
 4;70,67,83,82;,
 4;87,86,85,84;,
 4;89,68,69,88;,
 4;90,72,68,89;,
 4;92,74,72,91;,
 4;93,76,74,92;,
 4;97,96,95,94;,
 4;99,73,75,98;,
 4;103,102,101,100;,
 3;105,102,104;,
 4;109,108,107,106;,
 4;109,111,110,108;,
 4;111,113,112,110;,
 4;117,116,115,114;,
 4;121,120,119,118;,
 4;123,122,121,118;,
 4;125,124,122,123;,
 3;126,124,125;,
 3;127,124,126;,
 3;127,107,124;,
 4;131,130,129,128;,
 4;130,133,132,129;,
 3;136,135,134;,
 3;137,136,134;,
 3;137,138,136;,
 3;137,139,138;,
 3;137,140,139;,
 3;137,141,140;,
 3;137,142,141;,
 3;145,144,143;,
 4;149,148,147,146;,
 4;151,150,146,147;,
 4;149,154,153,152;,
 4;156,150,151,155;,
 4;155,158,157,156;,
 4;153,154,157,159;,
 3;162,161,160;,
 4;164,163,162,160;,
 4;166,163,164,165;,
 3;167,166,165;,
 4;169,160,161,168;,
 3;172,171,170;,
 4;168,171,172,169;,
 4;167,165,174,173;,
 4;176,175,173,174;,
 3;175,176,177;,
 4;162,163,170,161;,
 4;177,163,166,167;,
 4;178,176,155,151;,
 4;177,176,178,179;,
 4;171,168,161,170;,
 3;182,181,180;,
 4;144,185,184,183;,
 4;152,153,187,186;,
 4;191,190,189,188;,
 4;188,189,192,134;,
 3;180,194,193;,
 3;180,195,194;,
 3;196,195,180;,
 3;197,196,180;,
 3;181,197,180;,
 3;181,198,197;,
 3;181,199,198;,
 4;178,172,170,179;,
 4;167,173,175,177;,
 4;137,202,201,200;,
 4;202,205,204,203;,
 4;208,180,207,206;,
 4;210,205,208,209;,
 4;183,184,212,211;,
 4;211,213,181,183;,
 3;143,182,180;,
 4;134,215,214,188;,
 4;216,191,188,214;,
 3;218,217,189;,
 3;189,219,192;,
 4;147,172,178,151;,
 4;149,146,150,154;,
 4;150,156,157,154;,
 4;187,222,221,220;,
 4;223,186,187,220;,
 4;225,224,223,220;,
 4;221,226,225,220;,
 4;226,215,227,225;,
 4;227,213,224,225;,
 3;229,228,131;,
 3;130,131,230;,
 4;229,131,128,231;,
 4;233,229,231,232;,
 4;237,236,235,234;,
 4;241,240,239,238;,
 4;245,244,243,242;,
 3;243,247,246;,
 4;237,249,248,236;,
 4;253,252,251,250;,
 4;249,255,254,248;,
 4;259,258,257,256;,
 4;252,253,256,257;,
 3;259,255,258;,
 3;259,254,255;,
 3;259,260,254;,
 3;262,261,102;,
 3;261,263,102;,
 3;263,101,102;,
 3;105,264,102;,
 3;264,265,102;,
 3;265,262,102;,
 3;190,218,189;,
 3;157,158,159;,
 3;152,148,149;,
 3;169,172,147;,
 4;153,159,222,187;,
 3;208,143,180;,
 3;202,137,219;,
 3;185,144,266;,
 3;179,170,163;,
 3;163,177,179;,
 3;174,155,176;,
 3;243,244,267;,
 3;243,268,247;,
 3;243,267,269;,
 3;243,270,268;,
 3;243,269,271;,
 3;243,271,270;,
 3;266,144,145;,
 3;189,217,219;,
 3;230,273,272;,
 3;228,274,273;,
 3;272,273,227;,
 3;276,213,275;,
 3;181,276,277;,
 3;181,213,276;,
 3;273,274,227;,
 3;278,215,134;,
 3;280,279,215;,
 3;215,278,280;,
 4;215,279,272,227;,
 4;274,275,213,227;,
 4;144,183,181,182;,
 3;144,182,143;,
 3;134,192,137;,
 3;192,219,137;,
 3;131,228,273;,
 3;131,273,230;,
 4;112,281,116,117;,
 4;282,251,239,240;,
 3;283,204,205;,
 3;283,205,210;;
 
 MeshMaterialList {
  3;
  210;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
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
  259;
  -0.820183;-0.284208;-0.496513;,
  0.820183;-0.284208;-0.496513;,
  -0.689964;0.116384;-0.714426;,
  0.689964;0.116384;-0.714426;,
  -0.192965;-0.168138;0.966692;,
  0.192965;-0.168138;0.966692;,
  -0.190113;-0.305981;0.932862;,
  0.190113;-0.305981;0.932862;,
  -0.936832;-0.225730;-0.267192;,
  0.186330;-0.363424;0.912800;,
  -0.000000;-0.311666;0.950192;,
  -0.186330;-0.363424;0.912800;,
  -0.134421;-0.973177;0.186704;,
  0.134421;-0.973177;0.186704;,
  -0.513079;-0.352824;-0.782474;,
  0.894964;-0.192144;-0.402640;,
  0.000000;0.725285;-0.688448;,
  -0.894964;-0.192144;-0.402640;,
  0.936832;-0.225730;-0.267192;,
  -0.000000;-0.171359;0.985209;,
  0.000000;0.750989;-0.660315;,
  -0.000000;-0.369902;0.929071;,
  -0.000000;-0.982090;0.188414;,
  0.955505;-0.259806;-0.139682;,
  -0.955505;-0.259806;-0.139682;,
  -0.271205;0.511410;-0.815419;,
  0.000000;0.531323;-0.847169;,
  -0.297956;0.791339;-0.533858;,
  0.000000;0.828993;-0.559260;,
  0.271205;0.511410;-0.815419;,
  0.297956;0.791339;-0.533858;,
  0.568660;0.821337;0.045066;,
  0.000000;0.997095;-0.076164;,
  0.000000;0.989568;-0.144065;,
  0.448278;0.892642;-0.047300;,
  -0.568660;0.821337;0.045066;,
  -0.448278;0.892642;-0.047300;,
  -0.041153;0.982128;-0.183662;,
  0.000000;0.986431;-0.164175;,
  -0.043834;0.978156;-0.203196;,
  0.041153;0.982128;-0.183662;,
  0.043834;0.978156;-0.203196;,
  -0.203329;0.240475;-0.949120;,
  0.903929;-0.140757;-0.403857;,
  0.000000;0.081810;0.996648;,
  -0.196121;0.080221;0.977293;,
  0.203329;0.240475;-0.949120;,
  0.000000;0.245606;-0.969370;,
  0.000000;0.000000;-1.000000;,
  0.701560;-0.626197;-0.340135;,
  0.583147;-0.460137;-0.669488;,
  0.580395;-0.712244;-0.394778;,
  -0.788614;-0.556569;-0.261379;,
  -0.625155;-0.712426;-0.318794;,
  -0.828378;-0.450490;-0.332939;,
  -0.827315;-0.426360;-0.365741;,
  -0.785623;0.595175;0.169007;,
  0.632030;0.772143;0.065832;,
  -0.632030;0.772143;0.065832;,
  0.785613;0.595181;0.169030;,
  0.828363;-0.450411;-0.333084;,
  -0.001044;0.047202;-0.998885;,
  0.330013;0.100936;-0.938564;,
  -0.000413;-0.033514;-0.999438;,
  0.369291;-0.102912;-0.923598;,
  0.270440;-0.177708;-0.946193;,
  -0.963347;0.210149;-0.166735;,
  -0.956178;0.282499;-0.076925;,
  -0.654091;0.755349;-0.040161;,
  -0.214377;0.973475;0.079927;,
  0.391404;0.898445;0.198995;,
  0.750354;0.396425;0.528977;,
  0.724105;-0.045964;0.688157;,
  0.094954;-0.994029;0.053763;,
  -0.348817;-0.885485;-0.306991;,
  -0.825378;-0.402745;-0.395662;,
  -0.929582;-0.220091;-0.295698;,
  -0.956518;-0.010561;-0.291481;,
  -0.000084;-0.007948;-0.999968;,
  0.849197;-0.124275;-0.513245;,
  0.618118;0.028697;-0.785562;,
  -0.881712;-0.324755;-0.342226;,
  -0.932091;-0.359398;0.045167;,
  -0.982957;-0.175213;-0.055635;,
  -0.829664;-0.401902;0.387469;,
  -0.625102;-0.425044;0.654664;,
  -0.593892;-0.547936;0.589117;,
  0.542114;0.053207;-0.838619;,
  -0.690645;-0.528914;0.493213;,
  -0.000000;-0.642680;0.766134;,
  -0.000000;-0.614574;0.788860;,
  -0.542114;0.053207;-0.838619;,
  0.593892;-0.547936;0.589117;,
  0.829664;-0.401902;0.387469;,
  0.690645;-0.528914;0.493213;,
  -0.737895;-0.014544;-0.674759;,
  -0.692128;-0.065830;-0.718767;,
  -0.890170;-0.109703;-0.442224;,
  0.000001;0.197271;-0.980349;,
  0.000002;0.121401;-0.992604;,
  0.737894;-0.014549;-0.674759;,
  0.692126;-0.065842;-0.718768;,
  0.890168;-0.109709;-0.442227;,
  -0.926431;0.014573;-0.376182;,
  0.178744;-0.983698;-0.019713;,
  0.054728;-0.996191;0.067884;,
  0.475196;-0.877196;0.068677;,
  0.926431;0.014573;-0.376182;,
  0.831496;-0.464837;-0.304207;,
  0.474577;-0.235997;0.847987;,
  -0.178744;-0.983698;-0.019714;,
  0.000000;-0.998206;-0.059875;,
  -0.000000;-0.999712;0.023986;,
  -0.647971;0.025410;-0.761241;,
  -0.823858;-0.143167;-0.548417;,
  -0.989172;-0.133902;0.060082;,
  -0.753504;-0.159266;0.637860;,
  -0.173467;-0.263178;0.949024;,
  0.989172;-0.133902;0.060082;,
  0.932091;-0.359398;0.045167;,
  0.753504;-0.159266;0.637860;,
  -0.576816;0.206550;-0.790330;,
  -0.368860;0.065770;-0.927155;,
  -0.741642;-0.220451;-0.633537;,
  -0.723445;-0.354877;-0.592191;,
  -0.618457;-0.096959;-0.779814;,
  -0.782026;0.620051;0.063024;,
  -0.662610;0.461028;0.590255;,
  -0.702940;0.395952;-0.590845;,
  0.782026;0.620051;0.063024;,
  0.761096;0.322260;-0.562922;,
  0.662610;0.461028;0.590255;,
  0.000000;0.638838;0.769341;,
  0.000000;0.998149;0.060818;,
  -0.000032;0.672355;-0.740229;,
  0.717117;-0.332754;-0.612387;,
  0.347928;-0.885949;-0.306661;,
  -0.565874;-0.003138;-0.824486;,
  -0.416382;0.101723;-0.903481;,
  -0.095319;-0.993993;0.053773;,
  -0.322955;0.097686;-0.941359;,
  -0.367599;-0.103625;-0.924193;,
  0.217841;0.972328;0.084401;,
  0.917652;-0.290614;-0.271033;,
  0.653470;0.755877;-0.040345;,
  0.955771;0.283705;-0.077545;,
  0.285543;0.202238;-0.936784;,
  -0.843731;-0.433971;-0.315890;,
  0.843731;-0.433971;-0.315890;,
  0.513079;-0.352824;-0.782474;,
  0.304171;0.690920;-0.655828;,
  -0.304171;0.690920;-0.655828;,
  0.089558;-0.988913;0.118448;,
  -0.000000;-0.992903;0.118926;,
  -0.089558;-0.988913;0.118448;,
  -0.178354;-0.950706;0.253668;,
  -0.000000;-0.966198;0.257802;,
  0.178354;-0.950706;0.253668;,
  0.941143;-0.336413;-0.032812;,
  0.866741;-0.495556;0.056434;,
  0.898670;-0.424699;-0.109645;,
  0.898839;-0.320017;-0.299461;,
  0.978031;-0.013287;-0.208034;,
  -0.866741;-0.495556;0.056434;,
  -0.941143;-0.336413;-0.032812;,
  -0.898670;-0.424699;-0.109645;,
  -0.978031;-0.013287;-0.208034;,
  -0.898839;-0.320017;-0.299461;,
  0.883176;0.023016;-0.468477;,
  0.196121;0.080221;0.977293;,
  0.000000;0.066904;0.997759;,
  0.201490;0.065532;0.977296;,
  -0.201490;0.065532;0.977296;,
  -0.903929;-0.140757;-0.403857;,
  -0.883176;0.023016;-0.468477;,
  0.231489;0.730590;-0.642379;,
  -0.231489;0.730590;-0.642379;,
  0.000000;-0.182033;-0.983292;,
  -0.764470;-0.217939;-0.606703;,
  0.000000;0.130159;0.991493;,
  0.417433;0.118277;0.900977;,
  0.729407;0.331703;0.598279;,
  -0.937127;-0.241408;-0.252024;,
  0.870332;0.467343;0.155282;,
  0.138275;0.151645;0.978715;,
  0.764470;-0.217939;-0.606703;,
  -0.417433;0.118277;0.900977;,
  -0.729407;0.331703;0.598279;,
  0.937127;-0.241408;-0.252024;,
  -0.138275;0.151645;0.978715;,
  -0.870332;0.467343;0.155282;,
  0.736037;-0.618173;-0.275884;,
  0.596024;-0.724994;-0.345165;,
  -0.583909;-0.459937;-0.668961;,
  -0.560035;-0.743985;-0.364482;,
  -0.727742;-0.610746;-0.312060;,
  0.827310;-0.426381;-0.365729;,
  0.258307;-0.945995;0.195887;,
  0.000094;-0.979248;0.202666;,
  0.658810;-0.002888;-0.752304;,
  0.565077;-0.003710;-0.825030;,
  0.631073;0.288998;-0.719879;,
  0.576379;0.205226;-0.790993;,
  0.833787;-0.088506;-0.544946;,
  0.590634;-0.089099;-0.802006;,
  0.320249;0.135223;-0.937633;,
  0.369073;0.065785;-0.927069;,
  0.536409;0.343213;-0.771019;,
  -0.437357;-0.877764;0.195576;,
  0.625102;-0.425044;0.654664;,
  0.604466;-0.759299;0.241008;,
  -0.474577;-0.235997;0.847987;,
  -0.054728;-0.996191;0.067884;,
  -0.475196;-0.877196;0.068677;,
  0.129912;-0.987466;-0.089637;,
  0.000000;-0.994178;-0.107752;,
  0.082455;-0.991308;-0.102518;,
  -0.129911;-0.987466;-0.089637;,
  -0.082453;-0.991308;-0.102519;,
  -0.000000;-0.998456;0.055551;,
  0.177053;-0.981221;-0.076537;,
  -0.536320;0.344050;-0.770707;,
  -0.631356;0.290888;-0.718870;,
  -0.177053;-0.981221;-0.076537;,
  0.517925;0.230702;-0.823730;,
  0.402337;0.213941;-0.890143;,
  -0.517925;0.230702;-0.823730;,
  -0.402337;0.213941;-0.890143;,
  -0.000000;-0.416111;0.909314;,
  0.445710;0.196505;0.873343;,
  0.416574;0.102162;-0.903343;,
  -0.660020;-0.001902;-0.751246;,
  -0.258125;-0.946083;0.195699;,
  -0.724464;-0.046844;0.687719;,
  -0.746806;0.376114;0.548470;,
  -0.270727;-0.177575;-0.946137;,
  -0.395119;0.889497;0.229511;,
  0.974090;0.183784;-0.131804;,
  0.346123;-0.216477;-0.912873;,
  0.490900;0.098740;-0.865603;,
  0.439050;-0.226188;-0.869525;,
  0.430012;0.133414;-0.892911;,
  0.225607;-0.289113;-0.930331;,
  0.342109;-0.424265;-0.838427;,
  -0.277249;-0.960770;-0.007284;,
  -0.422116;0.135432;-0.896368;,
  -0.226461;-0.288758;-0.930233;,
  -0.490744;0.098716;-0.865694;,
  -0.342688;-0.423893;-0.838379;,
  -0.439232;-0.225913;-0.869505;,
  0.908535;-0.074643;-0.411086;,
  0.467406;0.371826;-0.802045;,
  -0.522694;0.353696;-0.775687;,
  -0.467543;0.371500;-0.802116;,
  -0.525329;0.294630;-0.798263;,
  -0.742630;0.056865;-0.667284;,
  0.525519;0.294473;-0.798195;,
  0.844689;0.071650;-0.530440;,
  0.000000;0.385757;-0.922600;;
  210;
  4;17,14,14,0;,
  4;149,15,1,149;,
  4;16,3,150,16;,
  4;2,16,16,151;,
  4;34,33,32,31;,
  4;33,36,35,32;,
  4;28,27,25,26;,
  4;30,28,26,29;,
  4;11,21,19,4;,
  4;21,9,5,19;,
  4;10,7,9,21;,
  4;6,10,21,11;,
  4;13,22,153,152;,
  4;22,12,154,153;,
  4;156,155,12,22;,
  4;157,156,22,13;,
  4;15,23,158,1;,
  4;23,160,159,158;,
  4;18,161,160,23;,
  4;162,18,23,15;,
  4;165,24,164,163;,
  4;24,17,0,164;,
  4;8,166,17,24;,
  4;167,8,24,165;,
  4;26,25,42,47;,
  4;168,168,43,43;,
  4;171,170,44,169;,
  4;29,26,47,46;,
  4;170,172,45,44;,
  4;174,174,173,173;,
  4;37,38,38,37;,
  4;33,34,175,20;,
  4;39,37,37,39;,
  4;38,40,40,38;,
  4;40,41,41,40;,
  4;36,33,20,176;,
  4;178,177,177,2;,
  4;179,181,180,179;,
  4;182,178,2,8;,
  4;181,183,34,31;,
  4;184,184,184,184;,
  4;177,185,3,177;,
  4;187,179,179,186;,
  4;185,188,18,3;,
  4;189,189,189,189;,
  4;190,187,35,36;,
  4;43,43,161,18;,
  4;169,44,19,5;,
  4;44,45,4,19;,
  4;173,173,8,167;,
  4;46,47,20,175;,
  4;47,42,176,20;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  3;49,192,191;,
  3;51,192,49;,
  3;51,50,192;,
  3;53,194,193;,
  3;53,195,194;,
  3;53,52,195;,
  4;54,195,52,54;,
  4;55,55,54,54;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,196,196;,
  4;49,191,60,60;,
  4;63,64,62,61;,
  3;65,64,63;,
  4;68,68,67,66;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;71,71,72,72;,
  4;73,198,197,73;,
  4;74,74,73,73;,
  4;75,76,74,74;,
  3;77,76,75;,
  3;66,76,77;,
  3;66,67,76;,
  4;78,200,199,50;,
  4;200,202,201,199;,
  3;204,203,79;,
  3;80,204,79;,
  3;80,205,204;,
  3;80,206,205;,
  3;80,202,206;,
  3;80,201,202;,
  3;80,207,201;,
  3;83,82,81;,
  4;86,84,208,85;,
  4;87,87,87,87;,
  4;86,90,89,88;,
  4;91,91,91,91;,
  4;210,93,92,209;,
  4;89,90,92,94;,
  3;96,97,95;,
  4;98,99,96,95;,
  4;101,99,98,100;,
  3;102,101,100;,
  4;81,95,97,103;,
  3;105,106,104;,
  4;211,211,211,211;,
  4;102,100,108,107;,
  4;109,109,109,109;,
  3;213,212,110;,
  4;216,215,104,214;,
  4;110,215,218,217;,
  4;112,212,210,219;,
  4;110,212,112,111;,
  4;106,220,214,104;,
  3;147,114,113;,
  4;82,88,116,115;,
  4;88,89,117,116;,
  4;120,94,119,118;,
  4;118,119,148,79;,
  3;113,222,221;,
  3;113,121,222;,
  3;122,121,113;,
  3;125,122,113;,
  3;114,125,113;,
  3;114,124,125;,
  3;114,123,124;,
  4;112,105,104,111;,
  4;217,223,213,110;,
  4;80,100,224,207;,
  4;100,98,225,224;,
  4;95,113,221,226;,
  4;227,98,95,226;,
  4;115,116,127,126;,
  4;126,128,114,115;,
  3;81,147,113;,
  4;79,130,129,118;,
  4;131,120,118,129;,
  3;93,210,119;,
  3;119,108,148;,
  4;208,105,112,219;,
  4;86,85,228,90;,
  4;228,209,92,90;,
  4;229,120,131,132;,
  4;127,116,117,132;,
  4;133,126,127,132;,
  4;131,129,133,132;,
  4;129,130,134,133;,
  4;134,128,126,133;,
  3;137,138,78;,
  3;200,78,230;,
  4;137,78,193,231;,
  4;121,137,231,222;,
  4;139,139,232,198;,
  4;233,234,234,233;,
  4;61,140,141,63;,
  3;141,235,63;,
  4;139,136,136,139;,
  4;142,142,236,236;,
  4;136,143,135,136;,
  4;237,145,144,144;,
  4;142,142,144,144;,
  3;237,143,145;,
  3;237,135,143;,
  3;238,238,135;,
  3;240,239,64;,
  3;239,241,64;,
  3;241,62,64;,
  3;65,242,64;,
  3;242,243,64;,
  3;243,240,64;,
  3;94,93,119;,
  3;92,93,94;,
  3;88,84,86;,
  3;244,105,208;,
  4;89,94,120,117;,
  3;95,81,113;,
  3;100,80,108;,
  3;88,82,84;,
  3;111,104,215;,
  3;215,110,111;,
  3;108,210,212;,
  3;141,140,245;,
  3;141,246,235;,
  3;141,245,247;,
  3;141,248,246;,
  3;141,247,249;,
  3;141,249,248;,
  3;84,82,83;,
  3;119,250,108;,
  3;230,146,251;,
  3;138,253,252;,
  3;251,146,134;,
  3;255,128,254;,
  3;114,255,123;,
  3;114,128,255;,
  3;252,253,134;,
  3;203,130,79;,
  3;257,256,130;,
  3;130,203,257;,
  4;130,256,251,134;,
  4;253,254,128,134;,
  4;82,115,114,147;,
  3;82,147,81;,
  3;79,148,80;,
  3;148,108,80;,
  3;78,138,146;,
  3;78,146,230;,
  4;70,70,71,71;,
  4;236,236,234,234;,
  3;258,225,98;,
  3;258,98,227;;
 }
 MeshTextureCoords {
  284;
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.375000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.656250;0.281250;,
  0.500000;0.250000;,
  0.343750;0.281250;,
  0.343750;0.281250;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.375000;0.375000;,
  0.656250;0.281250;,
  0.625000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.375000;0.625000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.500000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.875000;,
  0.375000;0.875000;,
  0.625000;0.875000;,
  0.593750;0.968750;,
  0.500000;1.000000;,
  0.406250;0.968750;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.843750;0.031250;,
  0.875000;0.125000;,
  0.843750;0.218750;,
  0.750000;0.250000;,
  0.156250;0.031250;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.156250;0.218750;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.343750;0.281250;,
  0.500000;0.250000;,
  0.500000;0.250000;,
  0.343750;0.281250;,
  0.500000;0.375000;,
  0.375000;0.375000;,
  0.375000;0.375000;,
  0.375000;0.375000;,
  0.656250;0.281250;,
  0.656250;0.281250;,
  0.625000;0.375000;,
  0.625000;0.375000;,
  0.625000;0.375000;,
  0.564777;0.500000;,
  0.564777;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.750000;,
  0.435223;0.500000;,
  0.435223;0.750000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.438836;0.495062;,
  0.465930;0.488355;,
  0.500000;0.474036;,
  0.534199;0.488362;,
  0.561172;0.495030;,
  0.615961;0.487522;,
  0.564777;0.495262;,
  0.861405;0.250000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.851139;0.103934;,
  0.625000;0.781323;,
  0.564777;0.787766;,
  0.499998;0.773912;,
  0.500002;0.773912;,
  0.435223;0.787766;,
  0.375000;0.781323;,
  0.148861;0.103934;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.138595;0.250000;,
  0.384039;0.487522;,
  0.435223;0.495294;,
  0.648534;0.137622;,
  0.656250;0.156250;,
  0.500000;0.150000;,
  0.589201;0.065930;,
  0.584318;0.049399;,
  0.500000;0.000000;,
  0.500000;0.444357;,
  0.500000;0.312500;,
  0.531250;0.312500;,
  0.531250;0.437245;,
  0.562500;0.312500;,
  0.562500;0.430596;,
  0.593750;0.312500;,
  0.591519;0.431193;,
  0.624988;0.344860;,
  0.625000;0.441926;,
  0.620315;0.442606;,
  0.598973;0.312528;,
  0.406250;0.438564;,
  0.375000;0.441926;,
  0.379388;0.328668;,
  0.406250;0.312500;,
  0.437500;0.312500;,
  0.437500;0.438843;,
  0.468750;0.312500;,
  0.468750;0.442600;,
  0.495015;0.446181;,
  0.500000;0.444356;,
  0.500000;0.146900;,
  0.511410;0.148410;,
  0.531912;0.190475;,
  0.500000;0.186956;,
  0.517051;0.136134;,
  0.540880;0.149496;,
  0.640489;0.202445;,
  0.632554;0.198071;,
  0.631582;0.193322;,
  0.625000;0.125000;,
  0.620710;0.168511;,
  0.571796;0.143205;,
  0.543211;0.148820;,
  0.519292;0.134833;,
  0.523069;0.125000;,
  0.312500;0.000000;,
  0.250000;0.125000;,
  0.156250;0.031250;,
  0.375000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.705607;,
  0.375000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.750000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.625000;,
  0.625000;0.705607;,
  0.625000;0.625000;,
  0.390625;0.921875;,
  0.375000;0.875000;,
  0.406250;0.968750;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.609375;0.921875;,
  0.593750;0.968750;,
  0.625000;0.875000;,
  0.375000;0.875000;,
  0.390625;0.921875;,
  0.417824;0.875000;,
  0.412374;0.875000;,
  0.412374;0.875000;,
  0.625000;0.875000;,
  0.609375;0.921875;,
  0.587626;0.875000;,
  0.587626;0.875000;,
  0.582176;0.875000;,
  0.500000;0.875000;,
  0.500000;0.875000;,
  0.375000;0.125000;,
  0.359511;0.202445;,
  0.326778;0.125000;,
  0.250000;0.186956;,
  0.140489;0.171467;,
  0.125000;0.125000;,
  0.375000;0.563044;,
  0.500000;0.563044;,
  0.750000;0.186956;,
  0.750000;0.125000;,
  0.875000;0.125000;,
  0.859511;0.171467;,
  0.673222;0.125000;,
  0.476931;0.125000;,
  0.480708;0.134833;,
  0.456937;0.148739;,
  0.428324;0.143155;,
  0.379321;0.168523;,
  0.368420;0.193354;,
  0.367452;0.198068;,
  0.525050;0.125000;,
  0.530566;0.125000;,
  0.625000;0.062500;,
  0.532106;0.125000;,
  0.522182;0.125000;,
  0.500000;0.062500;,
  0.469434;0.125000;,
  0.474950;0.125000;,
  0.375000;0.062500;,
  0.467894;0.125000;,
  0.477818;0.125000;,
  0.250000;0.250000;,
  0.156250;0.218750;,
  0.343750;0.281250;,
  0.750000;0.250000;,
  0.656250;0.281250;,
  0.843750;0.218750;,
  0.843750;0.031250;,
  0.854848;0.064545;,
  0.687500;0.000000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.563044;,
  0.375000;0.500000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.500000;0.250000;,
  0.470142;0.194507;,
  0.468260;0.190456;,
  0.530014;0.194559;,
  0.488628;0.148452;,
  0.482958;0.136140;,
  0.459277;0.149415;,
  0.379412;0.328662;,
  0.375000;0.441977;,
  0.406250;0.438612;,
  0.406250;0.312500;,
  0.625000;0.344841;,
  0.598953;0.312500;,
  0.620354;0.442651;,
  0.625000;0.441977;,
  0.589035;0.066001;,
  0.500000;0.150000;,
  0.656250;0.156250;,
  0.648447;0.137753;,
  0.584174;0.049413;,
  0.500000;0.000000;,
  0.437500;0.438889;,
  0.437500;0.312500;,
  0.591512;0.431221;,
  0.593750;0.312500;,
  0.562500;0.312500;,
  0.562500;0.430633;,
  0.468750;0.442644;,
  0.468750;0.312500;,
  0.531250;0.437299;,
  0.531250;0.312500;,
  0.500000;0.312500;,
  0.500000;0.444416;,
  0.495044;0.446230;,
  0.500000;0.312500;,
  0.389515;0.266735;,
  0.610485;0.266735;,
  0.389515;0.045765;,
  0.343750;0.156250;,
  0.145152;0.064545;,
  0.610485;0.266735;,
  0.389515;0.045765;,
  0.500000;0.312500;,
  0.343750;0.156250;,
  0.389515;0.266735;,
  0.564829;0.221204;,
  0.500000;0.198172;,
  0.435252;0.221188;,
  0.390788;0.232809;,
  0.362797;0.222562;,
  0.366703;0.201652;,
  0.633300;0.201653;,
  0.609217;0.232788;,
  0.637177;0.222526;,
  0.593750;0.431210;,
  0.593750;0.431238;,
  0.500000;0.125000;;
 }
}
