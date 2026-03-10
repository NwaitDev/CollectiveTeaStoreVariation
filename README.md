# Designing with Chips, Executing with BIP

## Abstract

The associated paper presents the compilation chain currently developed to design applications with the Chips description language and to turn these higher level specifications into component-based BIP implementations, thus benefiting from the correct-by-construction C++ code generation it provides. Along with the tool-chain, an extension of the Chips language inspired by aggregate programming is proposed. The additional features aim to precisely coordinate large ensembles of embedded processes while still letting the user tune the behaviour of the system according to control theory principles. The developments are illustrated by the simulation of an  application, namely an automatic load balancing web server. The compilation artifacts involved in the generation of the executable C++ code used to simulate these applications are presented, together with the results obtained by fine-tuning controllers integrated to make the system more resilient to environmental disturbances.

## Content of this repository

In this repository, at the root, you will find the following files:

- <code>TeaStoreVariation.chips</code>, the Chips designed model for the adaptive web server application.
- <code>chips1.1.ecore</code>, the metamodel of the Chips language, augmented to include collective primitives <code>spread</code> and <code>collect</code>. This artifact is also available in the Chips dedicated GitHub repository.
- <code>TeaStoreVariation.xmi</code>, the parsed version of the Chips model, respecting the specifications of the <code>chips1.1.ecore</code> metamodel,
- <code>bipinstaller.sh</code>, a linux bash script to quickly install the BIP compiler, the only requirement to replicate the experiments presented here. Run this script in the directory where you want BIP to be installed.
- <code>Dockerfile</code> and <code>compose.yaml</code> that allow to create a Docker image automating the full experiment.

And the following packages :
- the <code>Packages</code> folder, which contains all the different BIP/C++ artifacts generated to implement the behavior of each Chips component and collective primitive defined by the Chips model. Also note that the <code>Packages/IO</code> components and functions are not generated from the Chips specifications. It is a set of utility artifacts that can be (and are) introduced into the model description to output the states of the different signals that flow throug the model.
- the <code>MainApp</code> folder, which contains the BIP model of the <code>system</code> section of the Chips description. along with python scripts that can be used to merge and analyze the different traces written by the monitors tracking the state of the dataflows.
- And finally, the <code>NonCompilableArtifacts</code> folder, which contains:
  - a template for the implantation of a Chips Functionnal Block within the BIP framework,
  - a <code>.txt</code> file containing regular expressions to quickly eliminate uninteresting informations from the traces of compilation or execution of the model.
  - an <code>.ods</code> file that can be used with LibreOffice Calc to analyze the traces left by the monitors for the execution of the model that was used to write the tool paper,
  - <code>.png</code> exported graphics that were obtained from the <code>.ods</code> file mentionned in the previous item.