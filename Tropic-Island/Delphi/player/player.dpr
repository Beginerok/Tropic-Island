{Этот файл сгенерирован DeDe Ver 3.50.02 Copyright (c) 1999-2001 DaFixer}

Project player;

Uses
  Animate in 'Animate.pas' {TForm3},
  LibraryFunctions in 'LibraryFunctions.pas' {TForm2},
  MediaFunctions in 'MediaFunctions.pas' {TForm1};

{$R *.RES}

begin
{
0047B798   55                     push    ebp
0047B799   8BEC                   mov     ebp, esp
0047B79B   83C4F0                 add     esp, -$10
0047B79E   B878B54700             mov     eax, $0047B578

* Reference to: SysInit.@InitExe(Pointer);
|
0047B7A3   E8E4AEF8FF             call    0040668C

* Reference to TApplication instance
|
0047B7A8   A15CDB4700             mov     eax, dword ptr [$0047DB5C]
0047B7AD   8B00                   mov     eax, [eax]

* Reference to: Forms.TApplication.Initialize(TApplication);
|
0047B7AF   E850FCFDFF             call    0045B404

* Reference to TForm1 instance
|
0047B7B4   8B0D50DC4700           mov     ecx, [$0047DC50]

* Reference to TApplication instance
|
0047B7BA   A15CDB4700             mov     eax, dword ptr [$0047DB5C]
0047B7BF   8B00                   mov     eax, [eax]

* Reference to class TForm1
|
0047B7C1   8B15B88F4700           mov     edx, [$00478FB8]

* Reference to: Forms.TApplication.CreateForm(TApplication;TComponentClass;void;void);
|
0047B7C7   E850FCFDFF             call    0045B41C

* Reference to TForm2 instance
|
0047B7CC   8B0D88DC4700           mov     ecx, [$0047DC88]

* Reference to TApplication instance
|
0047B7D2   A15CDB4700             mov     eax, dword ptr [$0047DB5C]
0047B7D7   8B00                   mov     eax, [eax]

* Reference to class TForm2
|
0047B7D9   8B15EC864700           mov     edx, [$004786EC]

* Reference to: Forms.TApplication.CreateForm(TApplication;TComponentClass;void;void);
|
0047B7DF   E838FCFDFF             call    0045B41C

* Reference to TForm3 instance
|
0047B7E4   8B0D10DB4700           mov     ecx, [$0047DB10]

* Reference to TApplication instance
|
0047B7EA   A15CDB4700             mov     eax, dword ptr [$0047DB5C]
0047B7EF   8B00                   mov     eax, [eax]

* Reference to class TForm3
|
0047B7F1   8B15FC694700           mov     edx, [$004769FC]

* Reference to: Forms.TApplication.CreateForm(TApplication;TComponentClass;void;void);
|
0047B7F7   E820FCFDFF             call    0045B41C

* Reference to TApplication instance
|
0047B7FC   A15CDB4700             mov     eax, dword ptr [$0047DB5C]
0047B801   8B00                   mov     eax, [eax]

* Reference to: Forms.TApplication.Run(TApplication);
|
0047B803   E894FCFDFF             call    0045B49C

|
0047B808   E8538EF8FF             call    00404660
0047B80D   8D4000                 lea     eax, [eax+$00]
0047B810   0000                   add     [eax], al

}
end.
