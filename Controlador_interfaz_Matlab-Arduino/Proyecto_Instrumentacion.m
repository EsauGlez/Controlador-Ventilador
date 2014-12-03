function varargout = Proyecto_Instrumentacion(varargin)
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Proyecto_Instrumentacion_OpeningFcn, ...
                   'gui_OutputFcn',  @Proyecto_Instrumentacion_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end

function Proyecto_Instrumentacion_OpeningFcn(hObject, eventdata, handles, varargin)
handles.output = hObject;

guidata(hObject, handles);

function varargout = Proyecto_Instrumentacion_OutputFcn(hObject, eventdata, handles) 
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
rps_1 =get(hObject,'String');
rps = str2double(rps_1)
handles.edit1 = rps;
save rps

function edit1_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function pushbutton1_Callback(hObject, eventdata, handles)
load rps
arduino=serial('COM3','BAUD',9600);
fopen(arduino)
m=1;
n=[1:1:500];
%while(1)
for n=1:50
fprintf(arduino,'%u',rps);
A=fscanf(arduino,'%i')
    C(1,n) = A(1,1);
    set(handles.text4,'String',A);
    plot(C)
    ylim([0 40])
    xlim([0 50])
    drawnow
    
     if (C(1,n)==rps)
         m=m+1;
         if(m > 3)
             break;
         end
     else
         continue;
     end
end
fclose(INSTRFIND)
