package de.dopsy;
import org.eclipse.emf.codegen.ecore.*;
import org.eclipse.emf.ecore.EClassifier;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EcorePackage;

public class Helper {

	public static EClassifier getEcoreDataType(String name){
		
		return EcorePackage.eINSTANCE.getEClassifier(name);
	}
}
