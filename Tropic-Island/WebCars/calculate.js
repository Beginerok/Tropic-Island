function calculate()
{
  var Si=0;//document.getElementById("Si").value;
  var Ki=document.getElementById("Ki").value;
  var KR=0;//document.getElementById("KR").value;
  var P=0;//document.getElementById("P").value;
  var Ctco=0;//document.getElementById("Ctco").value;

  var Cr=document.getElementById("Cr").value;
  var Kr=document.getElementById("Kr").value;
  var Sp=document.getElementById("Sp").value;
  var Kp=document.getElementById("Kp").value;
  var Seo=document.getElementById("Seo").value;
  var Keo=document.getElementById("Keo").value;
  var Sm=document.getElementById("Sm").value;
  var Km=document.getElementById("Km").value;
  var So=document.getElementById("So").value;
  Ctco = parseFloat(Cr)*parseFloat(Kr)+parseFloat(Sp)*parseFloat(Kp)+parseFloat(Seo)*parseFloat(Keo)+
    parseFloat(Sm)*parseFloat(Km)+parseFloat(So);
document.getElementById('Ctco').value = Ctco;


  var Czg=0;//document.getElementById("Czg").value;
  var Sey=document.getElementById("Sey").value;
  var Kzg=document.getElementById("Kzg").value;
  Czg = parseFloat(Sey)*parseFloat(Kzg);
document.getElementById('Czg').value = Czg;

  var Iinfl=document.getElementById("Iinfl").value;
  var Nds=document.getElementById("Nds").value;
  var Bzp=0;//document.getElementById("Bzp").value;
  var Mrot=document.getElementById("Mrot").value;
  var Cnr=document.getElementById("Cnr").value;
  Bzp = parseFloat(Mrot)/parseFloat(Cnr);

  document.getElementById('Bzp').value = Bzp;
  var Dn=document.getElementById("Dn").value;
  var Dvp=document.getElementById("Dvp").value;
  var Drk=document.getElementById("Drk").value;
  var RO=0;//document.getElementById("RO").value;
  RO = (parseFloat(Bzp)+parseFloat(Dn)+parseFloat(Dvp)+parseFloat(Drk))/12.0;

  document.getElementById('RO').value = RO;
  var Y = document.getElementById("Y").value;
  var SV=0;//document.getElementById("SV").value;
  SV = (parseFloat(Bzp)+parseFloat(Dn)+parseFloat(Dvp)+parseFloat(Drk)+parseFloat(RO))*parseFloat(Y);

  document.getElementById('SV').value = SV;
  var U=0;//document.getElementById("U").value;

  var Ub=document.getElementById("Ub").value;
  var Ud1=document.getElementById("Ud1").value;
  var Ud2=document.getElementById("Ud2").value;
  var Ud3=document.getElementById("Ud3").value;
  var Ud4=document.getElementById("Ud4").value;
  var Ud5=document.getElementById("Ud5").value;
  U=parseFloat(Ub)+parseFloat(Ud1)+parseFloat(Ud2)+parseFloat(Ud3)+parseFloat(Ud4)+parseFloat(Ud5);
//  alert(U);
document.getElementById('U').value = U;
  Si = (parseFloat(Bzp)+parseFloat(Dn)+parseFloat(Dvp)+parseFloat(Drk)+parseFloat(RO)+parseFloat(SV))*parseFloat(U);
//  alert(Si);
document.getElementById('Si').value = Si;
  KR = parseFloat(Si)*parseFloat(Ki)*0.2;
document.getElementById('KR').value = KR;
  P = (parseFloat(Si)*parseFloat(Ki)+parseFloat(KR))*0.05;
document.getElementById('P').value = P;
  var NMCK = (parseFloat(Si)*parseFloat(Ki)+parseFloat(KR)+parseFloat(P)+parseFloat(Ctco)+
  parseFloat(Czg))*parseFloat(Iinfl)+parseFloat(Nds);

document.getElementById('result').value = NMCK;
  console.log(NMCK);
  alert(NMCK);
}
