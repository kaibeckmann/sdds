
package de.dopsy;

/**
 * Initialization support for running Xtext languages 
 * without equinox extension registry
 */
public class SDDS2StandaloneSetup extends SDDS2StandaloneSetupGenerated{

	public static void doSetup() {
		new SDDS2StandaloneSetup().createInjectorAndDoEMFRegistration();
	}
}

