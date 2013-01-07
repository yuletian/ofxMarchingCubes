#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(30, 32, 35);
	glEnable(GL_DEPTH_TEST);
	
	differentSurfaces = 0;
	drawGrid = true;
	mc.setResolution(32,16,32);
	mc.scale.set( 300, 150, 300 );
		
	normalShader.load("shaders/normalShader");
}

//--------------------------------------------------------------
void testApp::update(){
	float elapsedTime = ofGetElapsedTimef();
	
	if(differentSurfaces == 0){
		//NOISE
		float noiseStep = elapsedTime * .5;
		float noiseScale = .06;
		float noiseScale2 = noiseScale * 2.;
		for(int i=0; i<mc.resX; i++){
			for(int j=0; j<mc.resY; j++){
				for(int k=0; k<mc.resZ; k++){
					//noise
					float nVal = ofNoise(float(i)*noiseScale, float(j)*noiseScale, float(k)*noiseScale + noiseStep);
					if(nVal > 0.)	nVal *= ofNoise(float(i)*noiseScale2, float(j)*noiseScale2, float(k)*noiseScale2 + noiseStep);
					mc.setIsoValue( i, j, k, nVal );
				}
			}
		}
	}
	else if(differentSurfaces == 1){
		//SPHERES
		ofVec3f step = ofVec3f(3./mc.resX, 1.5/mc.resY, 3./mc.resZ) * PI;
		for(int i=0; i<mc.resX; i++){
			for(int j=0; j<mc.resY; j++){
				for(int k=0; k<mc.resZ; k++){;
					float val = sin(float(i)*step.x) * sin(float(j+elapsedTime)*step.y) * sin(float(k+elapsedTime)*step.z);
					val *= val;
					mc.setIsoValue( i, j, k, val );
				}
			}
		}
	}
	else if(differentSurfaces == 2){
		//SIN
		float sinScale = .5;
		for(int i=0; i<mc.resX; i++){
			for(int j=0; j<mc.resY; j++){
				for(int k=0; k<mc.resZ; k++){
					float val = sin(float(i)*sinScale) + cos(float(j)*sinScale) + sin(float(k)*sinScale + elapsedTime);
					mc.setIsoValue( i, j, k, val * val );
				}
			}
		}
	}
	
	//update the mesh
	mc.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    float elapsedTime = ofGetElapsedTimef();
    ofSetWindowTitle( ofToString( ofGetFrameRate() ) );
	
	camera.begin();
	
	//draw the mesh
	normalShader.begin();
	if(wireframe){
		mc.drawWireframe();
	}else{
		mc.draw();
	}
	normalShader.end();
	
	//draw the voxel grid
	if(drawGrid)	mc.drawGrid();
	
	camera.end();
	
	string info = "fps:" + ofToString(ofGetFrameRate()) +
	+ "\nnum vertices:" + ofToString(mc.vertexCount, 0)
	+ "\nthreshold:" + ofToString(mc.threshold)
    + "\n' ' changes surface type, currently " + surfaceTypes[differentSurfaces]
	
    + "\n's' toggles smoothing"
    + "\n'w' toggles wireframe"
    + "\n'f' flips normals"
    + "\n'g' toggles draw grid"
    + "\n'up/down' +- threshold";

	ofDrawBitmapString(info, 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	switch (key) {
		case 'w':
			wireframe = !wireframe;
			break;
			
		case 'f':
			mc.flipNormals();
			break;
			
		case 's':
			mc.setSmoothing( !mc.getSmoothing() );
			break;
			
		case 'g':
			drawGrid = !drawGrid;
			break;
			
		case ' ':
			differentSurfaces++;
			if(differentSurfaces>=3){
				differentSurfaces = 0;
			}
			break;
			
		case 'v':
			if(mc.getUsingVbo()){
				mc.useVbo( false );
			}else{
				mc.useVbo( true );
			}
			break;
			
		case OF_KEY_UP:
			mc.threshold += .03;
			break;
		case OF_KEY_DOWN:
			mc.threshold -= .03;
			break;
			
		default:
			break;
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
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