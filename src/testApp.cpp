#include "testApp.h"
#include "MSAShape3D.h"
//--------------------------------------------------------------

void testApp::setup(){
	areas = new Area[MAX_AREAS];
	nAreas=0;
	creando = false;
	modificar = false;
	modificar_area = false;
	creando_poli = false;
	vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
	aSeleccion = -1;
	pSeleccion = -1;
	rad_seleccion = 20;
}

//--------------------------------------------------------------
void testApp::update(){
	vidGrabber.grabFrame();

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	ofBackground(0);
	vidGrabber.draw(0,0);
	if(!creando&&!creando_poli)
		for(int i=0;i<nAreas;i++)
			areas[i].pintar();
	ofSetLineWidth(3);
	for(int i=0;i<nAreas;i++)
		areas[i].pintar_lineas(modificar);
	ofSetColor(255);
	ofDrawBitmapString("Tecla     funcion\nn         Nueva Area\nm         Modificar area",680,50);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='q')
	{
		for(int i=0;i<nAreas;i++)
		{
		}
		std::exit(1);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	if(key=='n'&&nAreas<MAX_AREAS&&!modificar)
	{
		nAreas++;
		creando = true;
		cout<<"Seleccione 3 vertices, Area# "<<nAreas<<endl;
	}
	if(key=='p'&&!modificar)
	{
		if(!creando_poli&&nAreas<MAX_AREAS)
		{
		nAreas++;
		creando_poli = true;
		cout<<"Seleccione el numero de vertices que desee y presione la tecla p al terminar."<<endl;
		areas[nAreas-1].es_poligono = true;
		areas[nAreas-1].vertices = new ofPoint[MAX_VERTEX];
		areas[nAreas-1].v_triang = new ofPoint[MAX_VERTEX];
		areas[nAreas-1].triangulo.reserve(MAX_VERTEX);
		}
		else
		{
			creando_poli = false;
			cout<<"Poligono terminado"<<endl;
			areas[nAreas-1].calcular_textura();
		}
	}
	if(key=='m')
	{
		modificar=(modificar==1)?0:1;
		if(modificar)
			modificar_area = false;
		cout<<"Modificar = "<<modificar<<endl;
	}
	if(key=='M')
	{
		modificar_area=(modificar_area==1)?0:1;
		if(modificar_area)
			modificar = false;
		cout<<"Modificar Area = "<<modificar_area<<endl;
	}
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(aSeleccion >= 0)
	{
		if(modificar)
		{
			areas[aSeleccion].v_triang[pSeleccion].x = mouseX;
			areas[aSeleccion].v_triang[pSeleccion].y = mouseY;
		}
		if(modificar_area)
		{
			areas[aSeleccion].vertices[pSeleccion].x = mouseX;
			areas[aSeleccion].vertices[pSeleccion].y = mouseY;
		}
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(modificar)
	{
		for(int i=0;i<nAreas;i++)
		{
			for(int j=0;j<areas[i].vCapturados;j++)
				if(ofDist(mouseX,mouseY,areas[i].v_triang[j].x,areas[i].v_triang[j].y)<rad_seleccion)
				{
					aSeleccion = i;
					pSeleccion = j;
				}

		}
	}
	if(modificar_area)
	{
		for(int i=0;i<nAreas;i++)
		{
			for(int j=0;j<3;j++)
				if(ofDist(mouseX,mouseY,areas[i].vertices[j].x,areas[i].vertices[j].y)<rad_seleccion)
				{
					aSeleccion = i;
					pSeleccion = j;
				}

		}
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(creando)
	{
		creando = areas[nAreas-1].capturar(x,y);
	}
	if(creando_poli)
	{
		areas[nAreas-1].caprutar_poli(x,y);
	}
	aSeleccion = -1;
	pSeleccion = -1;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}




